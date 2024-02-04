// ToiletStatus.js
import React, { useEffect, useState } from "react";
import styles from "./ToiletStatus.module.css";
import ToiletFooter from "../../layouts/ToiletFooter";
import ToiletHeader from "../../layouts/ToiletHeader";
import ToiletGrid from "./ToiletGrid";

const ToiletStatus = ({ selectFloor, restroomData }) => {
  const [restroomMen, setRestroomMen] = useState();
  const [restroomWomen, setRestroomWomen] = useState();
  useEffect(() => {
    if (restroomData !== undefined) {
      const men = restroomData.filter(
        (restroom) => restroom.floor === selectFloor && restroom.gender === 0
      );

      const women = restroomData.filter(
        (restroom) => restroom.floor === selectFloor && restroom.gender === 1
      );
      setRestroomMen([men[0]]);
      setRestroomWomen([women[0]]);
    }
  }, [selectFloor, restroomData]);

  return (
    <div className={styles.statusContainer}>
      <div className={styles.header}>
        <ToiletHeader />
      </div>
      <div className={styles.content}>
        <div className={styles.contentItem}>
          {restroomMen && restroomMen[0] != undefined ? (
            <ToiletGrid restroom={restroomMen} />
          ) : (
            <div> 화장실 없음 이미지</div>
          )}
        </div>
        <div className={styles.contentItem}>
          {restroomWomen && restroomWomen[0] != undefined ? (
            <ToiletGrid restroom={restroomWomen} />
          ) : (
            <div> 화장실 없음 이미지</div>
          )}
        </div>
      </div>
      <div className={styles.footer}>
        <ToiletFooter />
      </div>
    </div>
  );
};

export default ToiletStatus;
