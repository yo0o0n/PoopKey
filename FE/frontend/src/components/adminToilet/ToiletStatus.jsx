// ToiletStatus.js
import React from "react";
import styles from "./ToiletStatus.module.css";
import ToiletFooter from "../../layouts/ToiletFooter";
import ToiletHeader from "../../layouts/ToiletHeader";
import ToiletGrid from "./ToiletGrid";

const ToiletStatus = ({ selectFloor }) => {
  const data = selectFloor;
  return (
    <div className={styles.statusContainer}>
      <div className={styles.header}>
        <ToiletHeader />
      </div>
      <div className={styles.content}>
        <div className={styles.contentItem}>
          <ToiletGrid />
        </div>
        <div className={styles.contentItem}>
          <ToiletGrid />
        </div>
      </div>
      <div className={styles.footer}>
        <ToiletFooter />
      </div>
    </div>
  );
};

export default ToiletStatus;
