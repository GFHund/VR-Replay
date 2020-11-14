#include "ControlPanel.h"
#include "vendor/imgui/ImGuiFileDialog.h"

#include "EventSystem/EventManager.h"
#include "Data/DataLayer.h"
#include <iostream>

ControlPanel::ControlPanel(){
    EventManager::getInstance()->subscribe("DataOpened",this);
    mSessionType.push_back("-");
    mPlay = false;
    mReplayTime = 0.0f;
}

void ControlPanel::SetupWindow(){
    ImGui::Begin("Hello World");
    if (ImGui::Button("Open")){
        
        igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseRecordFile","Choose File",".sqlite3", ".");
    
    }
    if(igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseRecordFile")){
        if(igfd::ImGuiFileDialog::Instance()->IsOk == true){
            std::string filePathName = igfd::ImGuiFileDialog::Instance()->GetFilepathName();
            std::string filePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
            EventParam* param = new EventParam();
            param->setString("FilePath",filePath);
            param->setString("FilePathName",filePathName);
            std::cout << "ControlPanel" << std::endl;
            std::cout << filePath << std::endl;
            std::cout << filePathName << std::endl;
            EventManager::getInstance()->fireEvent("FileOpenEvent",param);
        }
        igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseRecordFile");
    }

    const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
    
    //ImGui::ListBox("listbox\n(single select)", &item_current, items, IM_ARRAYSIZE(items), 4);
    static int item_current = -1;
    int beforeItemCurrent = item_current;
    ImGui::Combo("Sessions", &item_current, mSessionType.data(), mSessionType.size());
    if(beforeItemCurrent != item_current){
        //I think the checkbox has changed his selection
        std::cout << "Select Box has changed" << std::endl;
    }

    if(mPlay == false){
        if(ImGui::Button("Play")){
            EventManager::getInstance()->fireEvent("PlayEvent");
            mPlay = true;
        }
    } else {
        if(ImGui::Button("Pause")){
            EventManager::getInstance()->fireEvent("PauseEvent");
            mPlay = false;
        }
    }
    
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void ControlPanel::event(std::string eventName,EventParam* param){
    if(eventName.compare("DataOpened") == 0){
        mSessionType.clear();
        mSessionType.push_back("-");
        std::vector<const char*> sessions = DataLayer::getInstance()->getSessions();
        mSessionType.insert(mSessionType.end(),sessions.begin(),sessions.end());

    }
}