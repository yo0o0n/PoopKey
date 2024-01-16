# 공통 PJT 2주차 

<br>

## 작성자 : 김영래\_1046042

<br>

## 1월 8일(월) - Javascript 복습

| 세부내용    | 완료여부           | 경로    | 참고자료    |
| ----------- | ------------------ | ------- | ----------- |
| `명세서 JS ` | :white_check_mark: | `./javascript/` | `JS 재입문 - https://developer.mozilla.org/ko/docs/Web/JavaScript/Language_overview` |
| `filter / map / reduce` | :white_check_mark: | `경로2` | `1학기 실습코드` |

---

<br>

## 1월 9일(화) - CSS복습 및 react 공부

| 세부내용                  | 완료여부             | 경로    | 참고자료                                                                                            |
| ------------------------- | -------------------- | ------- | --------------------------------------------------------------------------------------------------- |
| `생활코딩 React 영상강의` | :white_check_mark: | `./react-app/src/` | `생활코딩 https://youtube.com/playlist?list=PLuHgQVnccGMCOGstdDZvH41x0Vtvwyxu7&si=1VqiTTl-7rDHB1Kc` |
| `CSS 정렬 복습` | :white_large_square: | `./javascript/` | `1학기 실습코드`                                                                                         |

---


<br>

## 1월 10일(수) - react 공부 및 stm32 펌웨어 개발

| 세부내용    | 완료여부             | 경로    | 참고자료    |
| ----------- | -------------------- | ------- | ----------- |
| `생활코딩 React 영상강의` | :white_check_mark: | `./react-app/src/` | `생활코딩 https://youtube.com/playlist?list=PLuHgQVnccGMCOGstdDZvH41x0Vtvwyxu7&si=1VqiTTl-7rDHB1Kc` |
| `servo motor 제어` | :white_check_mark: | `./STM32F103RB/workspace_1.14.0/servo_ctrl/Core/Src/` | `stm32 reference manual` |

---

<br>

## 1월 11일(목) - 페이지 만들기 및 ra6e1 펌웨어 개발

| 세부내용    | 완료여부             | 경로    | 참고자료    |
| ----------- | -------------------- | ------- | ----------- |
| `리액트로 임의의 페이지 만들기` | :white_large_square: | `./react-app/src/` | `참고자료1` |
| `servo motor 제어` | :white_large_square: | `-` | `ra6e1 reference manual` |
| `git 협업 방법 정리` | :white_check_mark: | `./README.md `| `-`| 
---

<br>

## 1월 12일(금) - 아이디어 선정 및 명세서 작성으로 인한 금주 미해결 과제 보강

| 세부내용    | 완료여부             | 경로    | 참고자료    |
| ----------- | -------------------- | ------- | ----------- |
| `react강의 2개 강의` | :white_check_mark:   | `-` | `-` |
| ` filter / map / reduce ` | :white_large_square: | `-` | `-` |
| ` css ` | :white_large_square: | `-` | `-` |
| ` 임의 페이지 만들기 ` | :white_large_square: | `-` | `-` |
| ` ra6e1 servo motor 제어 ` | :white_large_square: | `-` | `-` |

---

<br>

## git 협업 방법 정리

1. git에 로그인한다.
```
git config --global user.name "김영래"
git config --global user.email "이메일"
```

2. 협업하는 git 프로젝트를 끌어온다
```
git clone git주소
```

3. 해당 프로젝트에서 작업을 완료하면, 내가 작업하는 동안 다음과 같은 문제가 발생할 수 있다.


- git과의 연결이 끊어짐, 이 경우를 확인하기 위해
```
git remote -v
``` 
만약 아무것도 출력이 없다면 연결이 끊어진거다.
```
git remote add origin master
```
로 해결한다.

- 작업하는 동안 다른 팀원이 git에 push를 했을 수 도 있다. 이 경우 충돌을 대비하여 pull 해야한다.

```
git pull

또는

git pull origin master
```

4. 프로젝트의 변경 사항을 담은다.
```
git add .
```

5. 커밋 메세지를 남긴다.
```
git commit -m "요약내용"
```

6. push한다.
```
git push origin master
```
끝.

<br>

## Template - 복사용도

| 세부내용    | 완료여부             | 경로    | 참고자료    |
| ----------- | -------------------- | ------- | ----------- |
| `세부내용1` | :white_check_mark:   | `경로1` | `참고자료1` |
| `세부내용2` | :white_large_square: | `경로2` | `참고자료2` |

---
