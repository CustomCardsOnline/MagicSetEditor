//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) 2001 - 2008 Twan van Laarhoven and "coppro"              |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/error.hpp>
#include <cli/text_io_handler.hpp>

DECLARE_TYPEOF_COLLECTION(ScriptParseError);

// ----------------------------------------------------------------------------- : Debug utilities

#if defined(_MSC_VER) && defined(_DEBUG)
	void msvc_assert(const char* msg, const char* expr, const char* file, unsigned line) {
		if (IsDebuggerPresent()) {
			char buffer[1024];
			if (msg) {
				sprintf(buffer, "Assertion failed: %s: %s, file %s, line %d\n", msg, expr, file, line);
			} else {
				sprintf(buffer, "Assertion failed: %s, file %s, line %d\n", expr, file, line);
			}
			OutputDebugStringA(buffer);
			DebugBreak();
		} else {
			_assert(expr, file, line);
		}
	}
#endif

// ----------------------------------------------------------------------------- : Error types

Error::Error(const String& message)
	: message(message)
{}

Error::~Error() {}

String Error::what() const {
	return message;
}

// ----------------------------------------------------------------------------- : Parse errors

ScriptParseError::ScriptParseError(size_t pos, int line, const String& filename, const String& error)
	: ParseError(error)
	, start(pos), end(pos), line(line), filename(filename)
{}
ScriptParseError::ScriptParseError(size_t pos, int line, const String& filename, const String& exp, const String& found)
	: ParseError(_("Expected '") + exp + _("' instead of '") + found + _("'"))
	, start(pos), end(pos + found.size()), line(line), filename(filename)
{}
ScriptParseError::ScriptParseError(size_t pos1, size_t pos2, int line, const String& filename, const String& open, const String& close, const String& found)
	: ParseError(_("Expected closing '") + close + _("' for this '") + open + _("' instead of '") + found + _("'"))
	, start(pos1), end(pos2 + found.size()), line(line), filename(filename)
{}
String ScriptParseError::what() const {
	return String(_("(")) << (int)start << _("): ") << Error::what();
}

String concat(const vector<ScriptParseError>& errors) {
	String total;
	FOR_EACH_CONST(e, errors) {
		if (!total.empty()) total += _("\n");
		total += e.what();
	}
	return total;
}
ScriptParseErrors::ScriptParseErrors(const vector<ScriptParseError>& errors)
	: ParseError(concat(errors))
{}

// ----------------------------------------------------------------------------- : Error handling

// Errors for which a message box was already shown
vector<String> previous_errors;
vector<String> previous_warnings;
String pending_errors;
String pending_warnings;
DECLARE_TYPEOF_COLLECTION(String);
wxMutex crit_error_handling;
bool write_errors_to_cli = false;

void show_pending_errors();
void show_pending_warnings();

void handle_error(const String& e, bool allow_duplicate = true, bool now = true) {
	{
		// Thread safety
		wxMutexLocker lock(crit_error_handling);
		// Check duplicates
		if (!allow_duplicate) {
			FOR_EACH(pe, previous_errors) {
				if (e == pe) return;
			}
			previous_errors.push_back(e);
		}
		// Only show errors in the main thread
		if (!pending_errors.empty()) pending_errors += _("\n\n");
		pending_errors += e;
	}
	// show messages
	if ((write_errors_to_cli || now) && wxThread::IsMain()) {
		show_pending_warnings(); // warnings are older, show them first
		show_pending_errors();
	}
}

void handle_error(const Error& e, bool allow_duplicate, bool now) {
	handle_error(e.what(), allow_duplicate, now);
}

void handle_warning(const String& w, bool now) {
	{
		// Check duplicates
		wxMutexLocker lock(crit_error_handling);
		// Check duplicates
		FOR_EACH(pw, previous_warnings) {
			if (w == pw) return;
		}
		previous_warnings.push_back(w);
		// Only show errors in the main thread
		if (!pending_warnings.empty()) pending_warnings += _("\n\n");
		pending_warnings += w;
	}
	// show messages
	if ((write_errors_to_cli || now) && wxThread::IsMain()) {
		show_pending_errors();
		show_pending_warnings();
	}
}

void handle_pending_errors() {
	show_pending_errors();
	show_pending_warnings();
}

void show_pending_errors() {
	assert(wxThread::IsMain());
	if (crit_error_handling.TryLock() != wxMUTEX_NO_ERROR)
		return;
	if (!pending_errors.empty()) {
		if (write_errors_to_cli) {
			cli.showError(pending_errors);
		} else {
			wxMessageBox(pending_errors, _("Error"), wxOK | wxICON_ERROR);
		}
		pending_errors.clear();
	}
	crit_error_handling.Unlock();
}
void show_pending_warnings() {
	assert(wxThread::IsMain());
	if (crit_error_handling.TryLock() != wxMUTEX_NO_ERROR)
		return;
	if (!pending_warnings.empty()) {
		if (write_errors_to_cli) {
			cli.showWarning(pending_warnings);
		} else {
			wxMessageBox(pending_warnings, _("Warning"), wxOK | wxICON_EXCLAMATION);
		}
		pending_warnings.clear();
	}
	crit_error_handling.Unlock();
}
