package com.project.poopkey.application.main.dao;

import com.project.poopkey.application.main.dto.Report;

public interface ReportDao {
    public void insert(Report report);
    // 적어도 몇번의 join 과정이 필요.
//    public List<Report> selectList(long);
}
