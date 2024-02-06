package com.project.poopkey.application.main.security.service;

import com.project.poopkey.application.main.security.JwtTokenProvider;
import com.project.poopkey.application.main.security.dao.MemberDao;
import com.project.poopkey.application.main.security.dto.Member;
import com.project.poopkey.application.main.security.dto.SignRequest;
import com.project.poopkey.application.main.security.dto.SignResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@Transactional
@RequiredArgsConstructor
public class SignService {
    private final MemberDao memberDao;
    private final PasswordEncoder passwordEncoder;
    private final JwtTokenProvider jwtTokenProvider;

    public SignResponse login(SignRequest request)throws Exception{
        Member member = memberDao.findByEmail(request.getEmail()).orElseThrow(()->
                new BadCredentialsException("잘못된 계정정보"));
        if(!passwordEncoder.matches(request.getPassword(), member.getPassword())){
            throw new BadCredentialsException("잘못된 계정정보");
        }
        return SignResponse.builder()
                .email(member.getEmail())
                .token(jwtTokenProvider.createToken(member.getEmail()))
                .build();
    }

    public boolean register(SignRequest request)throws Exception{
        try {
            Member member = Member.builder()
                    .email(request.getEmail())
                    .password(passwordEncoder.encode(request.getPassword()))
                    .build();
            memberDao.insertUser(member);
        }catch (Exception e){
            System.out.println(e.getMessage());
            throw new Exception("잘못된 요청");
        }
        return true;
    }
    public SignResponse getMember(String email) throws Exception{
        Member member = memberDao.findByEmail(email)
                .orElseThrow(()->new Exception("계정을 찾을 수 없음"));
        return new SignResponse(member);
    }
}
