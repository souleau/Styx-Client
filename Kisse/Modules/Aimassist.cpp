#include "Modules.h"
#include "../GUI/GUI.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
//bool enabled = false;
float snapSpeed = 5.0f;
bool mousePressedMode = false;
bool onlyTargetMode = false;
enum class AimMode {
	Snap,
	Smooth
};  
AimMode aimMode = AimMode::Snap;

void Kisse::Modules::Aimassist::run()
{

    if (!enabled || (mousePressedMode && !(GetKeyState(VK_LBUTTON) & 0x8000)) || GUI::draw || cache->theMinecraft.getCurrentScreen().isValid())
    {
        prev_selected_target.clear();
        return;
    }

    static Kisse::CTimer timer = std::chrono::milliseconds(10);
    if (!timer.isElapsed())
        return;

    Maths::Vector3d thePlayer_position = cache->thePlayer.getPosition();
    thePlayer_position.y += cache->thePlayer.getEyeHeight();

    Maths::Vector2d thePlayer_rotation = cache->thePlayer.getRotation();
    double cropped_thePlayer_yaw = Kisse::Maths::cropAngle180(thePlayer_rotation.x);
    double cropped_thePlayer_pitch = thePlayer_rotation.y;

    EntityPlayer selected_target{};
    double selected_target_YawToAdd = 0.0;
    double selected_target_PitchToAdd = 0.0;

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
  





        selected_target_YawToAdd += ((rand() / (double)RAND_MAX) * 0.2 - 0.1) * multiplier;
        selected_target_PitchToAdd += ((rand() / (double)RAND_MAX) * 0.2 - 0.1) * multiplierPitch;
        if (cropped_thePlayer_pitch + selected_target_PitchToAdd > 90.0)
            selected_target_PitchToAdd = 90.0 - cropped_thePlayer_pitch;
        else if (cropped_thePlayer_pitch + selected_target_PitchToAdd < -90.0)
            selected_target_PitchToAdd = -90.0 - cropped_thePlayer_pitch;
    }
    selected_target_YawToAdd += ((rand() / (double)RAND_MAX) * 0.05 - 0.025) * multiplier;
    selected_target_PitchToAdd += ((rand() / (double)RAND_MAX) * 1.05 - 0.50) * multiplierPitch;


    if (cropped_thePlayer_pitch + selected_target_PitchToAdd > 90.0)
        selected_target_PitchToAdd = 90.0 - cropped_thePlayer_pitch;
    else if (cropped_thePlayer_pitch + selected_target_PitchToAdd < -90.0)
        selected_target_PitchToAdd = -90.0 - cropped_thePlayer_pitch;


    for (EntityPlayer& target : Kisse::cache->playerEntities.toVector<EntityPlayer>())
    {
        if (!target.isValid() || target.isEqualTo(cache->thePlayer) || target.getTicksExisted() < 10)
            continue;

        AxisAlignedBB targetBB = target.getBoundingBox();
        Maths::Vector3d target_position
        (
            targetBB.getMinX() + (targetBB.getMaxX() - targetBB.getMinX()) / 2.0,
            targetBB.getMinY() + (targetBB.getMaxY() - targetBB.getMinY()) / 2.0,
            targetBB.getMinZ() + (targetBB.getMaxZ() - targetBB.getMinZ()) / 2.0
        );
        target_position = target_position + target.getMovementVector(cache->timer.getRenderPartialTicks());

        if (onlyTargetMode && prev_selected_target.isValid() && !prev_selected_target.isEqualTo(target))
            continue;

        Maths::Vector2d target_required_rotation = Maths::getYawPitch(thePlayer_position, target_position);
        double yawToAdd = target_required_rotation.x - cropped_thePlayer_yaw;
        double pitchToAdd = target_required_rotation.y - cropped_thePlayer_pitch;
        yawToAdd = Kisse::Maths::cropAngle180(yawToAdd);
        double target_distance = (target_position - thePlayer_position).distance();
        if (target_distance <= max_distance && target_distance > 0.5 && std::abs(yawToAdd) <= max_angle)
        {
            if (prev_selected_target.isValid() && prev_selected_target.isEqualTo(target))
            {
                selected_target = target;
                selected_target_YawToAdd = yawToAdd;
                selected_target_PitchToAdd = pitchToAdd;
                break;
            }
            if (!selected_target.isValid() || std::abs(yawToAdd) < std::abs(selected_target_YawToAdd))
            {
                selected_target = target;
                selected_target_YawToAdd = yawToAdd;
                selected_target_PitchToAdd = pitchToAdd;
            }
        }
        else if (prev_selected_target.isValid() && prev_selected_target.isEqualTo(target))
        {
            prev_selected_target.clear();
        }
    }

    if (selected_target.isValid())
    {
        prev_selected_target = selected_target;
        Kisse::Maths::Vector3d selected_target_mvmt_vec = selected_target.getMovementVector(cache->timer.getRenderPartialTicks());
        AxisAlignedBB selected_target_bb = selected_target.getBoundingBox();
        Kisse::Maths::Vector3d positionsToCheck[] =
        {
            Kisse::Maths::Vector3d(selected_target_bb.getMinX(), selected_target_bb.getMinY(), selected_target_bb.getMaxZ()) + selected_target_mvmt_vec,
            Kisse::Maths::Vector3d(selected_target_bb.getMaxX(), selected_target_bb.getMinY(), selected_target_bb.getMinZ()) + selected_target_mvmt_vec,
            Kisse::Maths::Vector3d(selected_target_bb.getMaxX(), selected_target_bb.getMinY(), selected_target_bb.getMaxZ()) + selected_target_mvmt_vec,
            Kisse::Maths::Vector3d(selected_target_bb.getMinX(), selected_target_bb.getMinY(), selected_target_bb.getMinZ()) + selected_target_mvmt_vec
        };
        double minYaw = 361.0, maxYaw = -1.0;
        double minPitch = 0.0, maxPitch = 0.0;
        for (const Kisse::Maths::Vector3d& position : positionsToCheck)
        {
            Kisse::Maths::Vector2d YawPitch = Maths::getYawPitch(thePlayer_position, position);
            double Yaw = YawPitch.x;
            if (Yaw < 0.0) Yaw += 360.0;
            if (Yaw < minYaw) minYaw = Yaw;
            if (Yaw > maxYaw) maxYaw = Yaw;
            maxPitch = YawPitch.y;
        }

        if (minYaw > 180.0) minYaw -= 360.0;
        if (maxYaw > 180.0) maxYaw -= 360.0;

        Kisse::Maths::Vector2d YawPitch = Maths::getYawPitch
        (
            thePlayer_position,
            Kisse::Maths::Vector3d(selected_target_bb.getMaxX(), selected_target_bb.getMaxY(), selected_target_bb.getMaxZ()) + selected_target_mvmt_vec
        );
        minPitch = YawPitch.y;


        const double transitionDuration = 200.0;
        double yawStep = (selected_target_YawToAdd - thePlayer_rotation.x) / transitionDuration;
        double pitchStep = (selected_target_PitchToAdd - thePlayer_rotation.y) / transitionDuration;


        if (aimMode == AimMode::Smooth && (std::abs(selected_target_YawToAdd - thePlayer_rotation.x) > 0.1 || std::abs(selected_target_PitchToAdd - thePlayer_rotation.y) > 0.1)) {
            thePlayer_rotation.x += yawStep;
            thePlayer_rotation.y += pitchStep;
        }
        else {


            thePlayer_rotation.x += selected_target_YawToAdd * (snapSpeed / 10.0f);
           // thePlayer_rotation.y += selected_target_PitchToAdd * (snapSpeed / 10.0f);
        }
        cache->thePlayer.setRotation(thePlayer_rotation);
    }
}


void Kisse::Modules::Aimassist::renderGUI()
{
  //  static bool showMultiplierPitch = false;
    ImGui::Checkbox("Enable", &enabled);
    // float snapSpeed = 10.0f;
    ImGui::SliderFloat("Max Distance", &max_distance, 1.0f, 6.0f, "%.1f");
    ImGui::SliderFloat("Max Angle", &max_angle, 10.0f, 180.0f, "%.1f");
    ImGui::SliderFloat("Horizontal Speed", &multiplier, 0.1f, 2.0f, "%.1f");
    ImGui::SliderFloat("Snap Speed", &snapSpeed, 0.0f, 10.0f, "%.1f");
    ImGui::Checkbox("Mouse Pressed", &mousePressedMode);
    ImGui::SameLine();
    ImGui::Checkbox("Only Target Mode", &onlyTargetMode);
    ImGui::NewLine();
    if (ImGui::Combo("Aim Mode", (int*)&aimMode, "Snap\0Smooth\0")) {

    }
}

void Kisse::Modules::Aimassist::render()
{
}

void Kisse::Modules::Aimassist::disable()
{
    prev_selected_target.clear();
}
