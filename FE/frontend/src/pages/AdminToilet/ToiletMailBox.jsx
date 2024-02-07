import styles from "./ToiletMailBox.module.css";
import React, { useEffect, useState, useRef } from "react";
import { updateMailCheck, getMailLocation } from "../../util/AdminAPI";
const ToiletMailBox = () => {
  const [mailList, setMailList] = useState();
  const [detailList, setDetailList] = useState([]);
  const [mailLocation, setMailLocation] = useState();
  const webSocket = useRef(null);

  // WebSocket
  useEffect(() => {
    webSocket.current = new WebSocket("ws://localhost:8080/ws/report");
    console.log(webSocket.current);

    webSocket.current.onopen = () => {
      console.log("웹소켓 연결 성공!!");
      const data = {
        masterId: 1, //로컬 스토리지에서 가져온다. or useParams 사용할것
      };
      const jsonData = JSON.stringify(data);
      sendMessage(jsonData);
    };

    webSocket.current.onerror = (error) => {
      console.log("웹소켓 연결 에러:", error);
    };

    webSocket.current.onmessage = (event) => {
      console.log("웹소켓 메시지 수신:", event.data);
      setMailList(
        JSON.parse(event.data).sort(function (o1, o2) {
          return o2.reportId - o1.reportId;
        })
      );
    };

    webSocket.current.onclose = (event) => {
      console.log("웹소켓 연결 종료:", event);
    };

    return () => {
      if (webSocket.current.readyState === WebSocket.OPEN) {
        webSocket.current?.close();
      }
    };
  }, []);

  // websocket 메시지 보내기
  const sendMessage = (message) => {
    if (webSocket.current.readyState === WebSocket.OPEN) {
      webSocket.current.send(message);
    }
  };

  const handleCheckedClick = async (reportId) => {
    try {
      await updateMailCheck(reportId);
      const data = {
        masterId: 1, //로컬 스토리지에서 가져온다. or useParams 사용할것
      };
      const jsonData = JSON.stringify(data);
      sendMessage(jsonData);
    } catch (e) {
      console.log(e);
    }
  };

  const handleOnDetailClick = (reportId) => {
    if (detailList.length == 0) {
      setDetailList([reportId]);
    } else {
      if (detailList.includes(reportId)) {
        setDetailList(
          detailList.filter((detail) => {
            if (detail != reportId) return detail;
          })
        );
      } else {
        setDetailList([...detailList, reportId]);
      }
    }
  };

  // stallId가 주어졌을 때 화장실 위치를 특정한다. (층, 성별, 칸 위치)
  const handleGetLocationClick = async (stallId) => {
    try {
      const response = await getMailLocation(stallId);
      const floor = `${response.floor}층 `;
      const gender = response.gender == 0 ? "남자화장실 " : "여자화장실";
      const location = `${findLocation(response.list, stallId)}번 칸 `;
      console.log(floor, gender, location, "화장실 위치 특정");

      setMailLocation({
        floor: floor,
        gender: gender,
        location: location,
      });
    } catch (e) {
      console.log(e);
    }
  };

  const findLocation = (list, stallId) => {
    for (let i = 0; i < list.length; i++) {
      if (list[i].stallId == stallId) {
        return i + 1;
      }
    }
  };

  return (
    <div>
      <div>
        <div className={styles.table}>
          <div className={styles.row}>
            <div className={styles.cell}>No</div>
            <div className={styles.cell}>신고사유</div>
            <div className={styles.cellContent}>신고내용</div>
          </div>

          {mailList &&
            mailList.map((mail, index) => {
              return (
                <div key={mail.reportId} className={styles.rowBox}>
                  <div
                    className={styles.row}
                    onClick={() => {
                      handleCheckedClick(mail.reportId);
                      handleOnDetailClick(mail.reportId);
                      handleGetLocationClick(mail.stallId);
                    }}
                  >
                    <div className={styles.cell}>{index + 1}</div>
                    <div className={styles.cell}>{mail.userReportReason}</div>
                    <div className={styles.cellContent}>{mail.content}</div>
                  </div>
                  {detailList && detailList.includes(mail.reportId) && (
                    <div className={styles.detail}>
                      위치정보:
                      {mailLocation && mailLocation.floor}
                      {mailLocation && mailLocation.gender}
                      {mailLocation && mailLocation.location}
                    </div>
                  )}
                </div>
              );
            })}
        </div>
      </div>
    </div>
  );
};

export default ToiletMailBox;
