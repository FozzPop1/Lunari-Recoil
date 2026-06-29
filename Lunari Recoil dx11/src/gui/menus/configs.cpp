#include "../../../inc/gui/menu.h"
#include "../../../inc/macro/config.h"

void ConfigMenu() {
    if (menu_idx == 1)
    {
        static std::vector<std::string> cfgs;
        static int selected = -1;

        auto Refresh = [&]()
        {
            cfgs = GetConfigFiles();
            if (selected >= (int)cfgs.size())
                selected = -1;
        };

        config.SetupConfigFolder();

        if (cfgs.empty())
            Refresh();

        // ---- Save ----
        ImGui::TextDisabled("Save Config");
        ImGui::Spacing();

        ImGui::SetNextItemWidth(-1);
        ImGui::InputText("##cfgname", ConfigSaveName, IM_ARRAYSIZE(ConfigSaveName), ImGuiInputTextFlags_AutoSelectAll);

        ImGui::Spacing();

        const bool hasName = ConfigSaveName[0] != '\0';
        const bool hasSelection = selected >= 0 && selected < (int)cfgs.size();

        if (!hasName) ImGui::BeginDisabled();
        if (ImGui::Button("Save", ImVec2(-1, 0)) && hasName)
        {
            config.SaveConfig(ConfigSaveName);
            Refresh();
        }
        if (!hasName) ImGui::EndDisabled();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // ---- Config list ----
        ImGui::TextDisabled("Configs");
        ImGui::SameLine();

        // Refresh button flush right
        float refreshWidth = ImGui::CalcTextSize("Refresh").x + ImGui::GetStyle().FramePadding.x * 2.0f;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - refreshWidth);
        if (ImGui::Button("Refresh"))
            Refresh();

        ImGui::Spacing();

        if (cfgs.empty())
        {
            ImGui::TextDisabled("No configs found.");
        }
        else
        {
            std::vector<const char*> items;
            items.reserve(cfgs.size());
            for (auto& c : cfgs)
                items.push_back(c.c_str());

            ImGui::SetNextItemWidth(-1);
            ImGui::ListBox("##cfglist", &selected, items.data(), (int)items.size(), 6);
        }

        ImGui::Spacing();

        // ---- Load / Delete ----
        if (!hasSelection) ImGui::BeginDisabled();

        if (ImGui::Button("Load", ImVec2(-1, 0)) && hasSelection)
        {
            std::string name = cfgs[selected];
            if (auto pos = name.find_last_of('.'); pos != std::string::npos)
                name = name.substr(0, pos);
            config.LoadConfig(name);
        }

        if (!hasSelection) ImGui::EndDisabled();
    }
}