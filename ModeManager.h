#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

class ModeManager {
public:
    ModeManager(int serviceModePin);
    void checkMode();
    bool isInServiceMode() const;

private:
    void enterServiceMode();
    void exitServiceMode();

    int m_serviceModePin;
    bool m_inServiceMode;
};

#endif
