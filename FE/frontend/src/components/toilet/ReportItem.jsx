import styles from "./ReportItem.module.css";
const ReportItem = ({
  id,
  report_img,
  report_descript,
  onClick,
  isSelected,
}) => {
  return (
    <div
      onClick={() => onClick(id)}
      className={[
        styles.ReportItem,
        isSelected ? styles.ReportItem_on_2 : styles.ReportItem_off,
      ].join(" ")}
    >
      <img src={report_img} />
      <span>{report_descript}</span>
    </div>
  );
};

export default ReportItem;
