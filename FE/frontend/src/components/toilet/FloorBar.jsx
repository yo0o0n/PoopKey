// FloorBar.js
import styles from "./FloorBar.module.css";
import React, { useEffect, useState } from "react";
import { getCongestion } from "../../util/API";
import CongestionItem from "./CongestionItem";

const FloorBar = ({ handleFloorClick, restroomData }) => {
  const [congestionData, setCongestionData] = useState();

  useEffect(() => {
    if (restroomData !== undefined) {
      const buildingId = restroomData[0].buildingId;
      const getCongestionData = async () => {
        try {
          const response = await getCongestion(buildingId);
          setCongestionData(response);
        } catch (e) {
          console.log(e);
        }
      };
      getCongestionData();
    }
  }, [restroomData]);

  //useEffert 사용하면서 데이터를 받아오고 setCongetstion으로 초기화 해주기
  //congestionData랑 데이터가 같은지 확인하기!!! (매우중요)
  console.log(congestionData, "화장실 혼잡도 데이터");
  return (
    <div className={styles.floorBar}>
      <div className={styles.floorList}>
        {restroomData &&
          restroomData.map((restroom) => {
            console.log(restroom, "레스트룸 데이터!!!!");
            // restroom.floor와 일치하는 화장실 혼잡 데이터 추출
            const currentFloorCongestion =
              congestionData &&
              congestionData.filter((data) => data.floor == restroom.floor);
            console.log(currentFloorCongestion, "현재층에 대한 혼잡도");
            if (restroom.gender === 0 && restroom.restroomId !== undefined) {
              return (
                <div
                  key={restroom.restroomId}
                  className={styles.floorItem}
                  onClick={() => handleFloorClick(restroom.floor)}
                >
                  <div className={styles.floorCongestion}>
                    <CongestionItem
                      status={
                        currentFloorCongestion &&
                        currentFloorCongestion[0].list[0].congestion
                      }
                    ></CongestionItem>

                    <CongestionItem
                      status={
                        currentFloorCongestion &&
                        currentFloorCongestion[0].list[1].congestion
                      }
                    ></CongestionItem>
                  </div>
                  <p className={styles.floorText}>{restroom.floor}</p>
                </div>
              );
            }
            return null;
          })}
      </div>
    </div>
  );
};

export default FloorBar;
