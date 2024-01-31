// FloorBar.js
import styles from "./FloorBar.module.css";
import React from "react";

const FloorBar = ({ handleFloorClick, toiletData }) => {
  console.log(typeof toiletData, 1);
  return (
    <div className={styles.floorBar}>
      <div className={styles.floorList}>
        {toiletData &&
          toiletData.data.map((toilet) => (
            <div key={toilet.id} onClick={() => handleFloorClick(toilet.title)}>
              {toilet.id}
            </div>
          ))}
      </div>
    </div>
  );
};

export default FloorBar;
