import styles from "./LoginHeader.module.css";
import { useEffect, useState } from "react";
import { Link } from "react-router-dom";

const LoginHeader = () => {
  const [isLogin, setIsLogin] = useState(false);

  useEffect(() => {
    if (localStorage.length > 0) {
      console.log(localStorage.getItem("id"), 1111);
      setIsLogin(true);
    } else {
      console.log("이게 넘어오면 안되는데..");

      setIsLogin(false);
    }
  }, []);

  const handleLogoutClick = (e) => {
    e.preventDefault();
    localStorage.clear();
    setIsLogin(false);
  };

  return (
    <div>
      {!isLogin ? (
        <span>
          <Link to="/login">로그인</Link>
          <Link to="/regist">회원가입</Link>
        </span>
      ) : (
        <div style={{ cursor: "pointer" }}>
          <a onClick={handleLogoutClick}>로그아웃</a>
        </div>
      )}
    </div>
  );
};
export default LoginHeader;
