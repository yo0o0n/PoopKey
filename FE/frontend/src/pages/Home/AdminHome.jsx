import style from "./AdminHome.module.css";
import { useEffect, useState, useRef } from "react";
import { useNavigate, useParams } from "react-router-dom";

const AdminHome = () => {
  const { buildingId } = useParams();
  const [msgCount, setMsgCount] = useState(0);
  const navigate = useNavigate();
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
      const mailData = JSON.parse(event.data);
      setMsgCount(mailData.filter((data) => data.checked == 0).length);
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

  // 메시지 보내기
  const sendMessage = (message) => {
    if (webSocket.current.readyState === WebSocket.OPEN) {
      webSocket.current.send(message);
    }
  };

  const handleStatusClick = () => {
    navigate(`/admin/toilet/${buildingId}`);
  };

  const handleRegistClick = () => {
    navigate(`/admin/toiletRegist/${buildingId}`);
  };

  const handleMailBoxClick = () => {
    navigate(`/admin/toiletMailBox`);
  };

  const handleStatisticClick = () => {
    navigate(`/admin/toiletStatistics/${buildingId}`);
  };
  return (
    <div>
      <div onClick={handleStatusClick}>화장실 현황</div>
      <div onClick={handleRegistClick}>화장실 등록</div>
      <div onClick={handleMailBoxClick}>화장실 알림 {msgCount}</div>
      <div onClick={handleStatisticClick}>화장실 통계</div>
    </div>
  );
};
export default AdminHome;
