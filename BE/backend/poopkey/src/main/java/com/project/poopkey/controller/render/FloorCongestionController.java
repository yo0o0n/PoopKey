package com.project.poopkey.controller.render;

import com.project.poopkey.model.dto.render.FloorCongestion;
import com.project.poopkey.model.service.render.FloorCongestionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

// 아직은 필요없어보이는 느낌. service와 웹소켓을 연결시키면 되니까.
// 문제없이 정상작동!!
@RestController
@RequestMapping("/test")
@CrossOrigin("*")
public class FloorCongestionController {
    @Autowired
    private FloorCongestionService floorCongestionService;
    @GetMapping("/{number}")
    public ResponseEntity<?> test(@PathVariable("number") long number){
        List<FloorCongestion> list = floorCongestionService.findFloorCongestionList(number);
        return new ResponseEntity<List<FloorCongestion>>(list, HttpStatus.OK);
    }
}
