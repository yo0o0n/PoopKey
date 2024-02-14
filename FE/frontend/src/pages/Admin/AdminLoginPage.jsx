import styles from "./AdminLoginPage.module.css";
import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import { userLogIn } from "../../util/API";

const AdminLoginPage = () => {
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
      const data = {
        email: loginData.email,
        password: loginData.password,
      };
      const response = await userLogIn(data);
      console.log("Login successful", response);

      // 로컬 스토리지에 저장
      // 현재는 보냈던 데이터를 다시 쓰고 있지만 서버에서 email, 이름, 서버 보내주면 좋음

      localStorage.removeItem("AdminToken");
      localStorage.removeItem("admin");
      localStorage.setItem("AdminToken", response.token);
      localStorage.setItem("admin", 1);

      navigate("/admin/1");
    } catch (error) {
      console.log("Login failed", error);
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
export default AdminLoginPage;
