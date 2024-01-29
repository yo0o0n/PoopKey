package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.dto.Bookmark;
import com.project.poopkey.application.main.dto.Report;
import com.project.poopkey.application.main.service.BookmarkService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class BookmarkController {
    // 토큰기반 회원 인증 절차를 추가해야 됨.
    @Autowired
    private BookmarkService bookmarkService;
    // http://{SERVER_URL}/api/user/bookmark
    @GetMapping("/user/bookmark")
    public ResponseEntity<?> bookmarkFind(@RequestParam("userId")int userId){
        List<Bookmark> list = bookmarkService.findList(userId);
        if(list==null || list.size()==0)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<List<Bookmark>>(list, HttpStatus.OK);
    }
}
