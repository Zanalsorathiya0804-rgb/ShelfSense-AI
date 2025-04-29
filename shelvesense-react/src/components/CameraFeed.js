import React, { useEffect, useRef } from 'react';

function CameraFeed() {
  const videoRef = useRef(null);

  useEffect(() => {
    // Set up WebSocket or HTTP streaming for real-time feed
    const videoStream = new WebSocket("ws://localhost:5000/feed"); // WebSocket endpoint to receive video frames
    videoStream.onmessage = (event) => {
      const imageData = event.data;  // Assuming the backend sends frame as a base64 image
      videoRef.current.src = imageData;  // Update the video feed
    };

    return () => {
      videoStream.close();
    };
  }, []);

  return (
    <div className="camera-feed">
      <h2>Real-Time Camera Feed</h2>
      <img ref={videoRef} alt="Camera Feed" width="100%" />
    </div>
  );
}

export default CameraFeed;
