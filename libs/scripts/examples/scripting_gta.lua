--[[
    Scripting examples using the LuaGLM binding API.

@NOTE: Examples not designed with performance in mind.
@LICENSE
    See Copyright Notice in lua.h
--]]
local glm = require("glm")

-- Cache common functions
local vec3 = vec3
local quat = quat
local glm_abs = glm.abs
local glm_deg = glm.deg
local glm_dot = glm.dot
local glm_rad = glm.rad
local glm_sign = glm.sign
local glm_approx = glm.approx

-- Cache direction vectors
local glm_up = glm.up()
local glm_right = glm.right()
local glm_forward = glm.forward()

--[[
    Example 1: ScreenPositionToCameraRay: gluUnProject implemented with data
    extracted from GTA V script natives.

    Details: Multiply a pixel position by the inverse of the cameras view and
    projection matrix. This implementation requires the screen coordinates to be
    on a [-1, 1] scale.
--]]
function ScreenPositionToCameraRay(screenX, screenY)
    local pos = GetFinalRenderedCamCoord()
    local rot = glm_rad(GetFinalRenderedCamRot(2))

    local q = glm.quatEulerAngleZYX(rot.z, rot.y, rot.x)
    return pos,glm.rayPicking(
        q * glm_forward,
        q * glm_up,
        glm_rad(GetFinalRenderedCamFov()),
        GetAspectRatio(true),
        0.10000, -- GetFinalRenderedCamNearClip(),
        10000.0, -- GetFinalRenderedCamFarClip(),
        screenX * 2 - 1, -- scale mouse coordinates from [0, 1] to [-1, 1]
        screenY * 2 - 1
    )
end

--[[
    Example 2: Convert a surface normal (often the result of a raycast) to a
    rotation usable by DrawMarker()

@NOTE This is a right-handed computation.
--]]
function SurfaceNormalToMarkerRotation(normal)
    local quat_eps = 1E-2
    local surfaceFlip = quat(180.0, glm_forward)

    -- If the surface normal is upwards or downwards, rotate the Z (heading) of
    -- the quaternion so any rendered texture/decal is directed towards the
    -- client camera.
    local q = nil
    if glm_approx(glm_abs(normal.z), 1.0, quat_eps) then
        local camRot = GetFinalRenderedCamRot(2)
        local counterRotation = (glm_sign(normal.z) * -camRot.z) - 90.0

        q = glm.quatlookRotation(normal, glm_right)
        q = q * quat(counterRotation, glm_up)

    -- There will always be edge-case issues when trying to precisely map a
    -- surface normal to a rotation usable by DRAW_MARKER: numerical stability,
    -- different eps values, normals approaching sin(x) == cos(x), not perfectly
    -- emulating the R* vector math library, etc.
    --
    -- Note ADD_DECAL uses direction vectors, simplifying the calculation
    -- significantly.
    elseif glm_approx(normal.y, 1.0, quat_eps) then
        q = glm.quatlookRotation(normal, -glm_up)
        surfaceFlip = quat(180.0, glm_right)
    else -- The texture/decal needs to be flipped!
        q = glm.quatlookRotation(normal, glm_up)
    end

    local euler = vec3(glm.extractEulerAngleYXZ(q * surfaceFlip))
    return q,glm_deg(vec3(euler[2],euler[1],euler[3]))
end

--[[
    Example 3: Take the result to a raycast test and create a decal that is
    mapped to the surface normal.

    See "decalType" and "PatchDecalDiffuseMap" for its limitations.
--]]
function CreateDecalFromRaycastResult(decalType, pos, surface, entity, textureSize)
    local decalEps = 1E-2  -- Decal properties
    local decalTimeout = -1.0

    local decalForward = -surface
    local decalRight = nil
    if IsEntityAVehicle(entity) then
        -- If the raycast intersects a vehicle, align the forward vector of the
        -- vehicle to the 'right' vector of the decal.
        local forward,right,up,_ = GetEntityMatrix(entity)

        local dot_forward = glm_dot(surface, forward)
        local dot_right = glm_dot(surface, right)
        if glm_approx(glm_abs(dot_forward), 1.0, decalEps) then
            decalRight = glm_sign(-dot_forward) * glm.projPlane(right, surface)
        elseif glm_approx(glm_abs(dot_right), 1.0, decalEps) then
            decalRight = glm_sign(dot_right) * forward
        else
            decalRight = glm.projPlane(forward, surface)
        end
    else
        -- Slightly adjust the position of the decal relative to the surface to
        -- 'massage' texture mapping/rage::decalClipper.
        pos = pos + surface * 0.0666

        -- Compute a perpendicular of the surface
        decalRight = glm.perpendicular(surface, -glm_up, glm_right)

        -- If the surface normal is upwards or downwards, rotate the Z (heading
        -- component) of the quaternion so any rendered texture/decal points
        -- towards the client camera.
        local dot_up = glm_dot(surface, glm_up)
        if glm_approx(glm_abs(dot_up), 1.0, decalEps) then
            local camRot = GetFinalRenderedCamRot(2)
            decalRight = quat(camRot.z, glm_up) * glm_right
        end
    end

    return AddDecal(decalType,
        pos.x, pos.y, pos.z,
        decalForward.x, decalForward.y, decalForward.z,
        decalRight.x, decalRight.y, decalRight.z,
        textureSize.x, textureSize.y,
        1.0, 1.0, 1.0, 1.0,
        decalTimeout, 1, 0, 1 -- float timeout, BOOL p17, BOOL p18, allowOnVehicles
    )
end

--[[
    @TODO: After some pre-specified amount of time without the texture
    dictionary being loaded: throw an error
--]]
function LoadStreamedTextureDict(dict, texture)
    Citizen.Trace(("Loading Texture Dictionary: %s\n"):format(dict))

    RequestStreamedTextureDict(dict)
    while not HasStreamedTextureDictLoaded(dict) do
        Citizen.Wait(0)
    end

    Citizen.Trace(("Loaded Texture Dictionary: %s\n"):format(dict))
end

Citizen.CreateThread(function()
    local activeDict,activeTexture = "GTAOlogo","GTAOTransitionLogo"
    --local activeDict,activeTexture = "ba_djposters","ls_solomun_poster_a"
    --local activeDict,activeTexture = "graffiti","Peace" -- Using customed streamed textures!

    -- The two dimensional size of the texture (prior to aspect adjustment)
    local activeSize = vec2(5.0, 5.0)
    LoadStreamedTextureDict(activeDict, activeTexture)

    -- Adjust the 'size' of the texture according to its aspect ratio.
    local activeRes = GetTextureResolution(activeDict, activeTexture)
    local activeDims = vec2(activeSize.x * (activeRes.x / activeRes.y), activeSize.y)

    -- Create a decalType with the provided textures.
    local decalType = 10001 -- Starting index of 'unbound' decalType
    PatchDecalDiffuseMap(decalType, activeDict, activeTexture)

    local activeHandle = nil
    while true do
        Citizen.Wait(0)

        SetMouseCursorActiveThisFrame()
        local mx = GetDisabledControlNormal(0, 239)
        local my = GetDisabledControlNormal(0, 240)

        -- Create a ray from the camera origin that extends through the mouse cursor
        local r_pos,r_dir = ScreenPositionToCameraRay(mx, my)
        local b = r_pos + 10000 * r_dir

        local handle = StartExpensiveSynchronousShapeTestLosProbe(r_pos.x,r_pos.y,r_pos.z, b.x,b.y,b.z, 1|2|8|16, PlayerPedId(), 7)
        local _,hit,pos,surface,entity = GetShapeTestResult(handle)
        if hit ~= 0 then -- Draw a preview using "DrawMarker":
            surface = glm.normalize(surface)

            -- Slightly adjust the position of the marker so the texture does
            -- not clip with flat surfaces
            local m_pos = pos + surface * 0.25
            local _,m_euler = SurfaceNormalToMarkerRotation(surface)
            DrawMarker(
                9, -- int type,
                m_pos.x,m_pos.y,m_pos.z, -- float posX, float posY, float posZ,
                0.0, 0.0, 0.0, -- float dirX, float dirY, float dirZ,
                m_euler.x,m_euler.y,m_euler.z, -- float rotX, float rotY, float rotZ
                activeDims.x,activeDims.y,activeDims.y, -- float scaleX, float scaleY, float scaleZ,
                255,255,255,123, -- int red, int green, int blue, int alpha,
                false, -- BOOL bobUpAndDown
                false, -- BOOL faceCamera
                2, -- int rotationOrder
                false, -- BOOL rotate,
                activeDict, activeTexture, -- char* textureDict, char* textureName
                false --  BOOL drawOnEnts
            )

            -- Create a decal
            if IsControlJustReleased(0, 51) then -- ~INPUT_CONTEXT~
                if activeHandle ~= nil then
                    RemoveDecal(activeHandle)
                    activeHandle = nil
                end

                activeHandle = CreateDecalFromRaycastResult(decalType, pos,surface,entity, activeDims)
            end
        end
    end
end)
