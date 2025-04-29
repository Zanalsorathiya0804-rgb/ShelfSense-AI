import React from 'react';

function Dashboard({ inventoryData }) {
  if (!inventoryData) {
    return <div>Loading...</div>;
  }

  return (
    <div className="dashboard">
      <h2>Inventory Dashboard</h2>
      <ul>
        {inventoryData.map((item, index) => (
          <li key={index}>
            <strong>{item.name}</strong>: {item.stock} in stock
          </li>
        ))}
      </ul>
    </div>
  );
}

export default Dashboard;
