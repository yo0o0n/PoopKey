import styles from "./SignupPage.module.css";
import React, { useState } from "react";
import axios from "axios";
import {
  emailCheck,
  passwordCheck,
  nameCheck,
  telCheck,
} from "../../util/InputCheck";

const SignupPage = () => {
  const [isEmailValid, setIsEmailValid] = useState(true);
  const [isPwValid, setIsPwValid] = useState(true);
  const [isNameValid, setIsNameValid] = useState(true);
  const [isTelValid, setIsTelValid] = useState(true);

  const [signupData, setSignupData] = useState({
    email: "",
    password: "",
    name: "",
    tel: "",
  });

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setSignupData({
      ...signupData,
      [name]: value,
    });

    if (name === "email") {
      if (emailCheck(value) || value === "") {
        setIsEmailValid(true);
        console.log("email 유효성 성공");
      } else {
        setIsEmailValid(false);
        console.log("email 유효성 실패");
      }
    }

    if (name === "password") {
      if (passwordCheck(value) || value === "") {
        setIsPwValid(true);
        console.log("pw 유효성 성공");
      } else {
        setIsPwValid(false);
        console.log("pw 유효성 실패");
        console.log(name);
      }
    }

    if (name === "name") {
      if (nameCheck(value) || value === "") {
        setIsNameValid(true);
        console.log("이름 유효성 성공");
      } else {
        setIsNameValid(false);
        console.log("이름 유효성 실패");
      }
    }

    if (name === "tel") {
      if (telCheck(value) || value === "") {
        setIsTelValid(true);
        console.log("전화번호 유효성 성공");
      } else {
        setIsTelValid(false);
        console.log("전화번호 유효성 실패");
      }
    }
  };

  const handleSignupSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await axios.post(
        `https://jsonplaceholder.typicode.com/posts`,
        signupData
      );
      console.log("Signup successful", response.data);
      // 여기에서 회원가입 후의 동작을 추가할 수 있습니다.
      // 회원 가입이 완료되었습니다.
      // 로그인 페이지로 이동
      window.location.replace("http://localhost:3000/login");
    } catch (error) {
      console.error("Signup failed", error);
      // 여기에서 회원가입 실패 시의 동작을 추가할 수 있습니다.
      alert("이미 존재하는 계정입니다.");
    }
  };

  return (
    <div className={styles.container}>
      <div>
        <h2>Pookey</h2>
        <form onSubmit={handleSignupSubmit}>
          <div>
            <input
              type="text"
              name="email"
              placeholder="Email"
              value={signupData.email}
              onChange={handleInputChange}
            />
          </div>
          <div className={styles.msg}>
            {!isEmailValid && `이메일 주소가 올바르지 않습니다.`}
          </div>

          <div>
            <input
              type="password"
              name="password"
              placeholder="Password"
              value={signupData.password}
              onChange={handleInputChange}
            />
          </div>
          <div className={styles.msg}>
            {!isPwValid &&
              `비밀번호는 영문,숫자,특수문자를 포함하여 8자 이상입니다.`}
          </div>

          <div>
            <input
              type="text"
              name="name"
              placeholder="Name"
              value={signupData.name}
              onChange={handleInputChange}
            />
          </div>
          <div className={styles.msg}>
            {!isNameValid && `이름이 올바르지 않습니다.`}
          </div>

          <div>
            <input
              type="text"
              name="tel"
              placeholder="Tel"
              value={signupData.tel}
              onChange={handleInputChange}
            />
          </div>
          <div className={styles.msg}>
            {!isTelValid && `전화번호 형식이 올바르지 않습니다.`}
          </div>
          <div className={styles.button}>
            <button type="submit">Sign Up</button>
          </div>
        </form>
      </div>
    </div>
  );
};
export default SignupPage;
