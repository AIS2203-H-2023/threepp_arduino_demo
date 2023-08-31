
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

#include <atomic>
#include <thread>

#include <iostream>

#include <serial/serial.h>
#include <nlohmann/json.hpp>

using namespace threepp;
using namespace nlohmann;

namespace {

    auto createBox(const Vector3& pos, const Color& color) {
        auto geometry = BoxGeometry::create();
        auto material = MeshBasicMaterial::create();
        material->color.copy(color);
        auto mesh = Mesh::create(geometry, material);
        mesh->position.copy(pos);

        return mesh;
    }

}// namespace

int main() {

    Canvas canvas("threepp demo", {{"antialiasing", 4}});
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 5;

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    auto group = Group::create();
    group->add(createBox({-1, 0, 0}, Color::green));
    group->add(createBox({1, 0, 0}, Color::blue));
    scene->add(group);

    renderer.enableTextRendering();
    auto& textHandle = renderer.textHandle("Hello World");
    textHandle.setPosition(0, canvas.getSize().height - 30);
    textHandle.scale = 2;

    std::array<float, 3> posBuf{};
    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
        ImGui::SetNextWindowSize({230, 0}, 0);
        ImGui::Begin("Demo");
        ImGui::SliderFloat3("position", posBuf.data(), -1.f, 1.f);
        controls.enabled = !ImGui::IsWindowHovered();
        ImGui::End();
    });

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height - 30);
    });

    int value1;
    int value2;
    std::atomic_bool stop = false;

    std::thread t([&]{
        serial::Serial serial("COM4", 9600);

        while (!stop && serial.isOpen()) {
            std::string line;
            try {
                line = serial.readline();
                json data = json::parse(line);

                value1 = data["potVal1"].get<int>();
                value2 = data["potVal2"].get<int>();

            } catch (const std::exception& e) {
                std::cerr << "Unable to parse '" << line << "'!" << std::endl;
            }
        }
    });

    canvas.animate([&] {
        renderer.render(scene, camera);

        group->rotation.x = math::mapLinear(static_cast<float>(value1), 0, 1024, -math::PI / 2, math::PI / 2);
        group->rotation.z = math::mapLinear(static_cast<float>(value2), 0, 1024, -math::PI / 2, math::PI / 2);

        ui.render();
        group->position.fromArray(posBuf);
    });

    stop = true;
    if (t.joinable()) t.join();
}
