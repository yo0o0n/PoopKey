import { useNavigate, useParams } from "react-router-dom";
import { useState } from "react";
import { createReportData } from "../../util/API";
import styles from "./ToiletReport.module.css";
import ReportItem from "./ReportItem";
import Moment from "moment";
import "moment/locale/ko"; //Locale Setting
const reportList = [
  {
    id: 0,
    report_img: process.env.PUBLIC_URL + `/assets/emotion1.png`,
    report_descript: "위생",
  },
  {
    id: 1,
    report_img: process.env.PUBLIC_URL + `/assets/emotion3.png`,
    report_descript: "파손",
  },
  {
    id: 2,
    report_img: process.env.PUBLIC_URL + `/assets/emotion5.png`,
    report_descript: "기타",
  },
];
const ToiletReport = () => {
  // 화장실칸 id, 화장실 id, content (Null), 신고사유 (select 태그 이용 위생:0, 파손:1, 기타:2)
  const [reason, setReason] = useState(0);
  const [content, setContent] = useState("");
  const { buildingId, stallId, floor } = useParams();
  const navigate = useNavigate();

  const handleClickEmotion = (reason) => {
    console.log(reason);
    setReason(reason);
  };

  const handleSubmit = () => {
    console.log(reason, content);
    const nowTime = Moment().format("YYYY-MM-DD HH:mm:ss");
    const data = {
      stallId: stallId, // 화장실칸ID
      content: content, // 신고내용
      userReportReason: reason, // 신고사유 (0: 위생, 1: 파손, 2: 기타)
    };
    createReportData(data);
    navigate(`/toilet/${buildingId}`, { state: { floor: floor } });
  };

  return (
    <div>
      <section>
        <h4>신고사유</h4>
        <div className={styles.report_list_wrapper}>
          {reportList.map((it) => (
            <ReportItem
              key={it.id}
              {...it}
              onClick={handleClickEmotion}
              //isSelected -> 선택된 아이템만 true -> style을 위한 변수
              isSelected={it.id === reason}
            />
          ))}
        </div>
      </section>
      <section>
        <h4>신고내용</h4>
        <div>
          <textarea
            className={styles.report_content}
            placeholder="신고내용을 입력해 주세요."
            value={content}
            onChange={(e) => setContent(e.target.value)}
          />
        </div>
      </section>
      <section>
        <button
          onClick={() =>
            navigate(`/toilet/${buildingId}`, { state: { floor: floor } })
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
