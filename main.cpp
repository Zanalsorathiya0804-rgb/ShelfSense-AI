#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using namespace cv;
using namespace dnn;
using namespace std;

// Function to get the names of the output layers of the neural network
vector<string> getOutputsNames(const Net& net) {
    static vector<string> names;
    if (names.empty()) {
        // Get unconnected output layers from the network
        vector<int> outLayers = net.getUnconnectedOutLayers();
        // Get the names of all layers in the network
        vector<string> layersNames = net.getLayerNames();
        names.resize(outLayers.size());
        // Store the names of output layers
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

// Function to draw the predicted bounding box and label on the frame
void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame, vector<string>& classes) {
    // Draw a rectangle around the detected object
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0, 255, 0), 3);
    
    // Prepare the label to display (class name and confidence)
    string label = format("%.2f", conf);
    if (!classes.empty()) {
        label = classes[classId] + ":" + label; // Display class name with confidence
    }

    // Add the label text on the frame
    putText(frame, label, Point(left, top - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2);
}

int main() {
    // Load the YOLO ONNX model
    Net net = readNet("yolov3-10.onnx");
    net.setPreferableBackend(DNN_BACKEND_OPENCV);  // Use OpenCV's DNN backend
    net.setPreferableTarget(DNN_TARGET_CPU);  // Use CPU for inference

    // Load class labels (e.g., coco.names)
    vector<string> classes;
    ifstream ifs("coco.names");
    string line;
    // Read the class names from the file
    while (getline(ifs, line)) classes.push_back(line);

    // Open the webcam for real-time video capture
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Cannot open webcam\n";  // Error if webcam is not opened
        return -1;
    }

    // Process frames until the user presses a key
    while (waitKey(1) < 0) {
        Mat frame;
        cap >> frame;  // Capture a new frame from the webcam
        if (frame.empty()) break;  // Exit if the frame is empty

        // Prepare the frame for the model (normalize and resize)
        Mat blob;
        blobFromImage(frame, blob, 1 / 255.0, Size(416, 416), Scalar(), true, false);
        net.setInput(blob);

        // Get the outputs from the network
        vector<Mat> outs;
        net.forward(outs, getOutputsNames(net));

        // Vectors to store detected object details
        vector<int> classIds;
        vector<float> confidences;
        vector<Rect> boxes;

        // Process the network's outputs
        for (auto& out : outs) {
            float* data = (float*)out.data;
            for (int i = 0; i < out.rows; ++i, data += out.cols) {
                // Extract scores from the network output
                Mat scores = out.row(i).colRange(5, out.cols);
                Point classIdPoint;
                double confidence;
                // Find the class with the highest confidence
                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                // If confidence is above a threshold (0.5), we keep this detection
                if (confidence > 0.5) {
                    // Get the bounding box dimensions (x, y, width, height)
                    int centerX = (int)(data[0] * frame.cols);
                    int centerY = (int)(data[1] * frame.rows);
                    int width = (int)(data[2] * frame.cols);
                    int height = (int)(data[3] * frame.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    // Store the class id, confidence, and bounding box
                    classIds.push_back(classIdPoint.x);
                    confidences.push_back((float)confidence);
                    boxes.push_back(Rect(left, top, width, height));
                }
            }
        }

        // Perform Non-Maximum Suppression to eliminate redundant overlapping boxes
        vector<int> indices;
        NMSBoxes(boxes, confidences, 0.5, 0.4, indices);
        // Draw the bounding boxes and labels on the frame
        for (int i : indices)
            drawPred(classIds[i], confidences[i], boxes[i].x, boxes[i].y,
                     boxes[i].x + boxes[i].width, boxes[i].y + boxes[i].height,
                     frame, classes);

        // Display the frame with detection results
        imshow("ShelfSense AI – Real-Time Detection", frame);
    }

    return 0;
}
