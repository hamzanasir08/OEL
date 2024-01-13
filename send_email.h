#ifndef SEND_EMAIL_H
#define SEND_EMAIL_H

void send_temp_warning_and_threat(const char *recipient, const char *sender, const char *logFilename, const char *temp_condition, double temp_c);

#endif  // SEND_EMAIL_H
