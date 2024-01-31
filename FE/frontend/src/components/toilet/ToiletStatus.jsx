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
    console.log("랜더링됨");

    if (restroomData !== undefined) {
      const men = restroomData.filter(
        (restroom) => restroom.floor === selectFloor && restroom.gender === 0
      );

      const women = restroomData.filter(
        (restroom) => restroom.floor === selectFloor && restroom.gender === 1
      );
      setRestroomMen(men);
      setRestroomWomen(women);
    }
    console.log(restroomData, "데이터 랜더링 잘됨");
  }, [selectFloor, restroomData]);

  return (
    <div className={styles.statusContainer}>
      <div className={styles.header}>
        <ToiletHeader />
      </div>
      <div className={styles.content}>
        <div className={styles.contentItem}>
          <ToiletGrid restroom={restroomMen} />
        </div>
        <div className={styles.contentItem}>
          <ToiletGrid restroom={restroomWomen} />
        </div>
      </div>
      <div className={styles.footer}>
        <ToiletFooter />
      </div>
    </div>
  );
};

export default ToiletStatus;
