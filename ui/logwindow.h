#ifndef __UI_LOGWINDOW_H__
#define __UI_LOGWINDOW_H__

#include <mutex>

#include <imgui.h>
#include "spdlog/sinks/base_sink.h"
#include "spdlog/details/format.h"


namespace ui {
    class LogWindow {
    public:
        LogWindow() {}
        void render(const char *title, bool *opened) {
            ImGui::SetNextWindowSize(ImVec2(500,400), ImGuiSetCond_FirstUseEver);
            ImGui::Begin(title, opened);

            if (ImGui::Button("Clear")) this->clear();
            ImGui::SameLine();
            bool copy_log = ImGui::Button("Copy");

            ImGui::Separator();

            ImGui::BeginChild("scrolling");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
            if (copy_log) ImGui::LogToClipboard();
            ImGui::TextUnformatted(buffer.begin());
            if (scrolldown)
                ImGui::SetScrollHere(1.0f);
            scrolldown = false;
            ImGui::PopStyleVar();
            ImGui::EndChild();
            ImGui::End();
        }

        void write(std::string text) {
            buffer.append(text.c_str());
            scrolldown = true;
        }

        void clear() {
            buffer.clear();
        }

    private:
        ImGuiTextBuffer buffer;
        bool scrolldown;
    };
}

class LogWindowSink : public spdlog::sinks::base_sink<std::mutex> {
public:
    explicit LogWindowSink(ui::LogWindow* log_window) : _log_window(log_window) {}
protected:
    void _sink_it(const spdlog::details::log_msg &msg) override {
        _log_window->write(msg.formatted.str());
    }
private:
    ui::LogWindow* _log_window;
};

typedef LogWindowSink LogWindowSink_mt;

#endif
