import styles from "./LoginPage.module.css";
import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";

const LoginPage = () => {
  const navigate = useNavigate();
  const [loginData, setLoginData] = useState({
    //이부분 실제 dto랑 맞춰줄 것
    email: "",
    password: "",
  });

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setLoginData({
      ...loginData,
      [name]: value,
    });
  };

  const handleLoginSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await axios.get(
        `https://jsonplaceholder.typicode.com/posts`,
        loginData
      );
      console.log("Login successful", response.data);

      // 로컬 스토리지에 저장
      // 현재는 보냈던 데이터를 다시 쓰고 있지만 서버에서 email, 이름, 서버 보내주면 좋음
      localStorage.clear();
      localStorage.setItem("id", loginData.email);
      localStorage.setItem("type", "member");
      navigate("/");
    } catch (error) {
      console.error("Login failed", error);
      // 여기에서 로그인 실패 시의 동작을 추가할 수 있습니다.
      alert("아이디 또는 비밀번호가 일치하지않습니다.");
    }
  };
  return (
    <>
      <form onSubmit={handleLoginSubmit}>
        <label>
          Email:
          <input
            type="text"
            name="email"
            value={loginData.email}
            onChange={handleInputChange}
          />
        </label>
        <br />
        <label>
          Password:
          <input
            type="password"
            name="password"
            value={loginData.password}
            onChange={handleInputChange}
          />
        </label>
        <br />
        <button type="submit">Login</button>
      </form>
    </>
  );
};
export default LoginPage;
