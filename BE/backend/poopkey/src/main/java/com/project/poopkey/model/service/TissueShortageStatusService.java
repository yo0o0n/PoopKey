package com.project.poopkey.model.service;

import com.project.poopkey.model.dto.TissueShortageStatus;

public interface TissueShortageStatusService {
    TissueShortageStatus findTissueShortageStatus(long stallId);
}
