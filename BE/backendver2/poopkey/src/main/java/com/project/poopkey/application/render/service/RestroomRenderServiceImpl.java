package com.project.poopkey.application.render.service;

import com.project.poopkey.application.render.dao.RestroomRenderDao;
import com.project.poopkey.application.render.dto.RestroomRender;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class RestroomRenderServiceImpl implements RestroomRenderService{

    @Autowired
    private RestroomRenderDao restroomRenderDao;

    @Override
    public RestroomRender findRestroomRender(int restroomId) {
        return restroomRenderDao.selectOne(restroomId);
    }
}
