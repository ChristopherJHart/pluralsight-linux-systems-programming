CC=gcc -Wall -Wextra

all: m7c3_basic_signals m7c4_basic_signal_handling m7c5_advanced_signal_handling m7c6_ignore_signals m7c7_terminate_gracefully m7c8_refresh_config m7c9_report_status m7c10_toggle_debugging m7c11_login_timeout m7c12_scheduled_events

m7c3_basic_signals: m7c3_basic_signals.c
	$(CC) -o m7c3_basic_signals $^

m7c4_basic_signal_handling: m7c4_basic_signal_handling.c
	$(CC) -o m7c4_basic_signal_handling $^

m7c5_advanced_signal_handling: m7c5_advanced_signal_handling.c
	$(CC) -o m7c5_advanced_signal_handling $^

m7c6_ignore_signals: m7c6_ignore_signals.c
	$(CC) -o m7c6_ignore_signals $^

m7c7_terminate_gracefully: m7c7_terminate_gracefully.c
	$(CC) -o m7c7_terminate_gracefully $^

m7c8_refresh_config: m7c8_refresh_config.c
	$(CC) -o m7c8_refresh_config $^

m7c9_report_status: m7c9_report_status.c
	$(CC) -o m7c9_report_status $^

m7c10_toggle_debugging: m7c10_toggle_debugging.c
	$(CC) -o m7c10_toggle_debugging $^

m7c11_login_timeout: m7c11_login_timeout.c
	$(CC) -o m7c11_login_timeout $^

m7c12_scheduled_events: m7c12_scheduled_events.c
	$(CC) -o m7c12_scheduled_events $^

clean:
	rm -f m7c3_basic_signals
	rm -f m7c4_basic_signal_handling
	rm -f m7c5_advanced_signal_handling
	rm -f m7c6_ignore_signals
	rm -f m7c7_terminate_gracefully
	rm -f m7c8_refresh_config
	rm -f m7c9_report_status
	rm -f m7c10_toggle_debugging
	rm -f m7c11_login_timeout
	rm -f m7c12_scheduled_events
