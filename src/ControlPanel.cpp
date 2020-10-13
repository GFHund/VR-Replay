#include "ControlPanel.h"
#include "vendor/imgui/ImGuiFileDialog.h"
#include "EventSystem/EventManager.h"
#include <iostream>
void ControlPanel::SetupWindow(){
    ImGui::Begin("Hello World");
    if (ImGui::Button("Open")){
        std::cout << "Button Clicked" << std::endl;
        igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseRecordFile","Choose File",".sqlite", ".");
    
    }
    if(igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseRecordFile")){
        if(igfd::ImGuiFileDialog::Instance()->IsOk == true){
            std::string filePathName = igfd::ImGuiFileDialog::Instance()->GetFilepathName();
            std::string filePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
            
        }
        igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseRecordFile");
    }
    
    ImGui::End();
}