import styles from "./CongestionItem.module.css";

const CongestionItem = ({ status }) => {
  console.log(status, "status 값이 잘 넘어옴");
  const congestion0 = process.env.PUBLIC_URL + `/assets/emotion1.png`;

  const congestion1 = process.env.PUBLIC_URL + `/assets/emotion3.png`;

  const congestion2 = process.env.PUBLIC_URL + `/assets/emotion5.png`;

  return (
    <div>
      {status == 0 && <img src={congestion0} className={styles.statusImg} />}
      {status == 1 && <img src={congestion1} className={styles.statusImg} />}
      {status == 2 && <img src={congestion2} className={styles.statusImg} />}
    </div>
  );
};

export default CongestionItem;
