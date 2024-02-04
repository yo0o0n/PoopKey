import styles from "./StateChange.module.css";
import { useNavigate, useParams } from "react-router-dom";
import { useState } from "react";
import { updateStatus } from "../../util/AdminAPI"; // 점검 변경하는 axios
import StateItem from "./StateItem";
import "moment/locale/ko"; //Locale Setting
const reportList = [
  {
    id: 0,
    report_img: process.env.PUBLIC_URL + `/assets/emotion1.png`,
    report_descript: "사용가능",
  },
  {
    id: 3,
    report_img: process.env.PUBLIC_URL + `/assets/emotion3.png`,
    report_descript: "점검중",
  },
];
const ToiletReport = () => {
  // 화장실칸 id, 화장실 id, content (Null), 신고사유 (select 태그 이용 위생:0, 파손:1, 기타:2)
  const [state, setState] = useState(0);
  const { buildingId, stallId, floor } = useParams();
  const navigate = useNavigate();

  const handleClickEmotion = (state) => {
    console.log(state);
    setState(state);
  };

  const handleSubmit = async () => {
    // const nowTime = Moment().format("YYYY-MM-DD HH:mm:ss");
    const data = {
      stallId: stallId, // 화장실칸ID
      state: state, // 변경 내용 (사용가능:0 , 점검중:3)
    };
    await updateStatus(data);
    navigate(`/admin/toilet/${buildingId}`, { state: { floor: floor } });
  };

  return (
    <div>
      <section>
        <h4>신고사유</h4>
        <div className={styles.report_list_wrapper}>
          {reportList.map((it) => (
            <StateItem
              key={it.id}
              {...it}
              onClick={handleClickEmotion}
              //isSelected -> 선택된 아이템만 true -> style을 위한 변수
              isSelected={it.id === state}
            />
          ))}
        </div>
      </section>
      <section>
        <button
          onClick={() =>
            navigate(`/admin/toilet/${buildingId}`, {
              state: { floor: floor },
            })
          }
        >
          취소하기
        </button>
        <button onClick={handleSubmit}> 제출하기 </button>
      </section>
    </div>
  );
};

export default ToiletReport;
