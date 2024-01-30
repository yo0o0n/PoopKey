import { useNavigate } from "react-router-dom";
import { useState } from "react";
import {} from "../../util/API";
import styles from "./StateChange.module.css";
import StateItem from "./StateItem";
import Moment from "moment";
import "moment/locale/ko"; //Locale Setting
const stateList = [
  {
    id: 0,
    state_img: process.env.PUBLIC_URL + `/assets/emotion1.png`,
    state_descript: "사용가능",
  },
  {
    id: 1,
    state_img: process.env.PUBLIC_URL + `/assets/emotion3.png`,
    state_descript: "점검",
  },
];
const StateChange = () => {
  // 화장실칸 id, 화장실 id, content (Null), 신고사유 (select 태그 이용 위생:0, 파손:1, 기타:2)
  const [state, setState] = useState(0);
  const navigate = useNavigate();

  const handleClickEmotion = (state) => {
    console.log(state);
    setState(state);
  };

  const handleSubmit = () => {
    const nowTime = Moment().format("YYYY-MM-DD HH:mm:ss");
    const data = {
      //상태 변경하는 컨트롤러
      reportId: 4,
      stallId: 2, // 화장실칸ID
      //createdDate: nowTime,
      state: state, // 신고사유
    };

    //createReportData(data); //상태변경할 api
  };

  return (
    <div>
      <section>
        <h4>상태변경</h4>
        <div className={styles.state_list_wrapper}>
          {stateList.map((it) => (
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
        <button onClick={() => navigate(-1)}> 취소하기 </button>
        <button onClick={handleSubmit}> 변경하기 </button>
      </section>
    </div>
  );
};

export default StateChange;
