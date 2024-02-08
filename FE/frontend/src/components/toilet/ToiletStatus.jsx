// ToiletStatus.js
import React, { useEffect, useState } from "react";
import styles from "./ToiletStatus.module.css";
import ToiletGrid from "./ToiletGrid";
import { useSearchParams } from "react-router-dom";

const ToiletStatus = ({ selectFloor, restroomData }) => {
  const [restroomMen, setRestroomMen] = useState();
  const [restroomWomen, setRestroomWomen] = useState();
  const [searchParams] = useSearchParams();

  useEffect(() => {
    if (restroomData !== undefined) {
      const men = restroomData.filter(
        (restroom) => restroom.floor == selectFloor && restroom.gender == 0
      );

      const women = restroomData.filter(
        (restroom) => restroom.floor == selectFloor && restroom.gender == 1
      );
      setRestroomMen([men[0]]);
      setRestroomWomen([women[0]]);
    }
  }, [selectFloor, restroomData]);

  return (
    <div className={styles.statusContainer}>
      <div className={styles.header}>
        <div className={styles.title}>Pookey</div>
        <div className={styles.floor}>{selectFloor}F</div>
      </div>
      <div className={styles.content}>
        <div className={styles.itemBox}>
          <p className={styles.textItem}>Men</p>
          <div className={styles.gridItem}>
            {restroomMen && restroomMen[0] != undefined ? (
              <ToiletGrid restroom={restroomMen} />
            ) : (
              <div> 화장실 없음 이미지</div>
            )}
          </div>
        </div>
        <div className={styles.itemBox}>
          <p className={styles.textItem}>Women</p>
          <div className={styles.gridItem}>
            {restroomWomen && restroomWomen[0] != undefined ? (
              <ToiletGrid restroom={restroomWomen} />
            ) : (
              <div> 화장실 없음 이미지</div>
            )}
          </div>
        </div>
      </div>

      <div className={styles.footer}>
        <div className={styles.status}>
          화장실칸 상태 정보
          <div>
            <div>사용가능</div>
            <div>고장</div>
            <div>사용중</div>
            <div>점검중</div>
          </div>
        </div>
        <div className={styles.congestion}>
          화장실층 상태 정보
          <div>
            <div></div>
            <div>혼잡</div>
            <div>포화</div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default ToiletStatus;
