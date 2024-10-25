


#include "rendering.h"


int main() {
    system1 system;
    

    rendering ren(512, 512);

    int key = 0;
    double fps = 0.0;
    cv::TickMeter tm;
    while (1) {
        tm.start();

        for (int i = 0; i < 10; i++)
            system.update();
        ren.clear();
        ren.draw(system.get_data(), system.rest_length);

        tm.stop();
        double timeSec = tm.getTimeSec() / tm.getCounter();
        if (timeSec > 0) {
            fps = 1 / timeSec;
        }

        std::string fpsText = cv::format("FPS: %.2f", fps);
        cv::Mat image(512, 512, CV_32FC3, ren.get_frame()->data());
        std::string text = "Spring_Stiffness: " + std::string(std::to_string(system.get_stiffness()));
        std::string text1 = "Damping: " + std::string(std::to_string(system.get_damping()));
        std::string text2 = "FPS: " + std::string(fpsText);
        // 设置文本的起始位置（左下角）
        cv::Point textOrg(10, 30); // 略微偏离左上角，以便文本清晰可见
        cv::Point textOrg1(10, 50); // 略微偏离左上角，以便文本清晰可见
        cv::Point textOrg2(10, 70); // 略微偏离左上角，以便文本清晰可见
        // 设置字体（查看文档了解更多字体选项）
        int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        // 设置字体缩放比例
        double fontScale = 0.5;
        // 设置字体颜色为白色
        cv::Scalar color(255, 255, 255);
        // 设置字体粗细
        double thickness = 1.5;
        // 在图像上绘制文本
        cv::putText(image, text, textOrg, fontFace, fontScale, color, thickness);
        cv::putText(image, text1, textOrg1, fontFace, fontScale, color, thickness);
        cv::putText(image, text2, textOrg2, fontFace, fontScale, color, thickness);

        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);

        key = cv::waitKey(10);


        if (key == 's')
            system.add_damping();
        else if (key == 'S') {
            system.minus_damping();
        } else if (key == 'd')
            system.add_stiffness();
        else if (key == 'D')
            system.minus_stiffness();
        else if(key=='c')
            system.clear();
        else if (key == 27)
            break;

        tm.reset(); // 重置计时器
        cv::setMouseCallback("image", system1::onMouse, &system);

    }
    return 0;
}