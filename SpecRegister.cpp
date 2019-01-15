
#include "stdafx.h"

#include "SpecRegister.h"

std::unordered_map<std::string, std::string> SpecRegister::event_filter_rule_map;
std::unordered_map<std::string, std::string> SpecRegister::event_capture_rule_map;
std::unordered_map<std::string, std::string> SpecRegister::cq_rule_map;
std::unordered_map<std::string, std::string> SpecRegister::cep_rule_map;

void SpecRegister::register_event_filter_rule(string output_target, string rules) {
	event_filter_rule_map[output_target] = rules;
}

void SpecRegister::register_event_capture_rule(string output_target, string rules) {
	event_capture_rule_map[output_target] = rules;
}

void SpecRegister::register_cq_rule(string output_target, string rules) {
	cq_rule_map[output_target] = rules;
}

void SpecRegister::register_cep_rule(string output_target, string rules) {
	cep_rule_map[output_target] = rules;
}

string SpecRegister::query_event_filter_rule(string output_target) {
	return event_filter_rule_map[output_target];
}

string SpecRegister::query_event_capture_rule(string output_target) {
	return event_capture_rule_map[output_target];
}

string SpecRegister::query_cq_rule(string output_target) {
	return cq_rule_map[output_target];
}

string SpecRegister::query_cep_rule(string output_target) {
	return cep_rule_map[output_target];
}

bool SpecRegister::delete_event_filter_rule(string output_target) {
	event_filter_rule_map.erase(output_target);
	return true;
}

bool SpecRegister::delete_event_capture(string output_target) {
	event_capture_rule_map.erase(output_target);
	return true;
}

bool SpecRegister::delete_cq_rule(string output_target) {
	cq_rule_map.erase(output_target);
	return true;
}

bool SpecRegister::delete_cep_rule(string output_target) {
	cep_rule_map.erase(output_target);
	return true;
}