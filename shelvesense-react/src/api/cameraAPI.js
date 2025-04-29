// This file handles all API requests (e.g., camera feed, inventory updates, etc.)
export const fetchInventoryData = async () => {
    try {
      const response = await fetch('http://localhost:5000/inventory');
      const data = await response.json();
      return data;
    } catch (error) {
      console.error("Error fetching inventory data:", error);
      return [];
    }
  };
  