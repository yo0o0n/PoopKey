package com.project.poopkey.model.service;

import com.project.poopkey.model.dao.ToiletBreakStatusDao;
import com.project.poopkey.model.dto.ToiletBreakStatus;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ToiletBreakStatusServiceImpl implements ToiletBreakStatusService{

    @Autowired
    private ToiletBreakStatusDao toiletBreakStatusDao;

    @Override
    public ToiletBreakStatus findToiletBreakStatus(long stallId) {
        return toiletBreakStatusDao.selectOne(stallId);
    }
}
