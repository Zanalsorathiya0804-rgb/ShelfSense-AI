import React, { useState, useEffect } from 'react';

function AlertNotification({ inventoryData }) {
  const [alerts, setAlerts] = useState([]);

  useEffect(() => {
    if (inventoryData) {
      // Check for low stock items and add alerts
      const lowStockItems = inventoryData.filter(item => item.stock <= item.lowStockThreshold);
      if (lowStockItems.length > 0) {
        setAlerts(lowStockItems);
      }
    }
  }, [inventoryData]); // Runs when inventory data changes

  const dismissAlert = (itemName) => {
    // Remove the alert when the user dismisses it
    setAlerts((prevAlerts) => prevAlerts.filter((alert) => alert.name !== itemName));
  };

  return (
    <div className="alert-notifications">
      {alerts.length > 0 ? (
        <div>
          <h3>Low Stock Alerts</h3>
          {alerts.map((alert, index) => (
            <div key={index} className="alert-item">
              <div className="alert-content">
                <strong>{alert.name}</strong> is running low on stock! Only {alert.stock} left.
              </div>
              <button onClick={() => dismissAlert(alert.name)}>Dismiss</button>
            </div>
          ))}
        </div>
      ) : (
        <p>No alerts at the moment!</p>
      )}
    </div>
  );
}

export default AlertNotification;
