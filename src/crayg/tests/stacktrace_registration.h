//
// Created by Jan on 17.08.2019.
//
#include <signal.h>

#include <boost/stacktrace.hpp>
#include <iostream>

void print_stack_trace() {
  std::cout << boost::stacktrace::stacktrace() << std::endl;
}
void signal_handler_segv(int signum) {
  ::signal(signum, SIG_DFL);
  std::cerr << "invalid memory access (segmentation fault)" << std::endl;

  print_stack_trace();

  ::raise(SIGABRT);
}
void signal_handler_abrt(int signum) {
  ::signal(signum, SIG_DFL);

  std::cerr << "abnormal termination condition, as is e.g. initiated by std::abort()" << std::endl;

  print_stack_trace();

  ::raise(SIGABRT);
}
void signal_handler_ill(int signum) {
  ::signal(signum, SIG_DFL);

  std::cerr << "invalid program image, such as invalid instruction" << std::endl;

  print_stack_trace();

  ::raise(SIGABRT);
}
void signal_handler_fpe(int signum) {
  ::signal(signum, SIG_DFL);

  std::cerr << "erroneous arithmetic operation such as divide by zero" << std::endl;

  print_stack_trace();

  ::raise(SIGABRT);
}
std::string status_string(bool status) {
  return status ? "registrered" : "not registered";
}

bool sig_sev_registered = false;
bool sig_abrt_registered = false;
bool sig_ill_registered = false;
bool sig_fpe_registered = false;

void register_signal_handlers() {
  sig_sev_registered = ::signal(SIGSEGV, &signal_handler_segv) != SIG_ERR;
  sig_abrt_registered = ::signal(SIGABRT, &signal_handler_abrt) != SIG_ERR;
  sig_ill_registered = ::signal(SIGILL, &signal_handler_ill) != SIG_ERR;
  sig_fpe_registered = ::signal(SIGFPE, &signal_handler_fpe) != SIG_ERR;
}

std::string signal_handler_registration_report() {
  return "SIGSEGV handler: " + status_string(sig_sev_registered) + " \n" +
      "SIGABRT handler: " + status_string(sig_abrt_registered) + "\n" +
      "SIGILL handler: " + status_string(sig_ill_registered) + "\n" +
      "SIGFPE handler: " + status_string(sig_fpe_registered);
}

