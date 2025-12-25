# ShelfSense AI – Real-Time Smart Inventory Monitoring for Small Shops
## Project Summary

**ShelfSense AI** is a real-time smart inventory monitoring system designed to help small shops (such as grocery stores, pharmacies, mobile stores, etc.) automatically track products on their shelves. By leveraging AI, computer vision, and real-time data processing, the system detects and monitors product stock levels to reduce stock-outs, understocking, and inefficient inventory management.

## Problem Statement

Small shops face several challenges with manual inventory tracking:
- **Stock-outs**: Products run out of stock without timely replenishment.
- **Understocking**: Shop owners may not know when certain items need to be restocked.
- **Inefficient Management**: Manual checks can be time-consuming and prone to human error.

These problems lead to lost sales, poor customer experience, and inefficient use of time.

## Solution

ShelfSense AI addresses these challenges by providing a smart, AI-powered system for tracking inventory. The system provides:
- **Real-Time Product Detection**: Captures live images of product shelves using a camera.
- **AI-Powered Object Detection**: Utilizes the YOLO (You Only Look Once) model to identify products and monitor stock levels.
- **Low-Stock Alerts**: Sends notifications to shop owners when products are running low or out of stock.
- **Inventory Forecasting**: Predicts when stock will run out based on current sales trends.
- **Web Dashboard**: Displays a visual representation of inventory status and trends.

## Project Features

- **Real-Time Monitoring**: Continuously tracks inventory using live camera feeds.
- **AI Object Detection**: Uses the YOLO model to detect products on shelves.
- **Low-Stock Alerts**: Sends notifications when inventory levels are low.
- **Inventory Dashboard**: Provides a web dashboard to display product status, stock alerts, and sales trends.
- **SQLite Integration**: Stores inventory data (product names, stock levels) locally.

## Technologies Used

- **C++**: Backend development for real-time camera feed processing, object detection, and database management (SQLite).
- **OpenCV**: For capturing and processing live images from the camera.
- **TensorFlow C++ API or OpenCV DNN**: For loading and running the pre-trained YOLO model for object detection.
- **SQLite**: Local storage for inventory data (product names, stock levels).
- **React.js**: For creating the frontend web dashboard to visualize inventory data and stock alerts.


