import React, { useState, useEffect } from 'react';
import CameraFeed from './components/CameraFeed';
import Dashboard from './components/Dashboard';
import './App.css';

function App() {
  const [inventoryData, setInventoryData] = useState(null);

  // Example: Fetch inventory data from your backend (this could be real-time inventory info)
  useEffect(() => {
    fetch('http://localhost:5000/inventory')  // Your backend API endpoint
      .then(response => response.json())
      .then(data => setInventoryData(data));
  }, []);

  return (
    <div className="App">
      <h1>ShelfSense AI - Smart Inventory Monitoring</h1>
      <CameraFeed />
      <Dashboard inventoryData={inventoryData} />
    </div>
  );
}

export default App;
