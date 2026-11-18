% cweb-hy-fix.cls: the class cweb-hy (cweb-hy.cls + cwbasehy.tex) with
% repaired hyperlinks and commas in the index, without changing those
% files. Use it instead of cweb-hy, with the same options:
%   \documentclass[baseclass=article]{cweb-hy-fix}
% hyperref may be loaded before or after; the link fixes are applied at
% \begin{document}.
%
% Problems in cweb-hy:
%
% (1) cweave marks a section that was changed by a change file with the
%     change flag \* after its number, e.g. \M{75\*} or "75\*" in the
%     index and in the cross references. cweb-hy builds hyperlink names
%     and anchor names directly from this raw number, e.g.
%     _hyperchunk_75\*. The flag \* expands to different things in the
%     anchor (section start) and in the link (index), so the names never
%     agree, and all links to changed sections are dead.
%
% (2) The index, the cross references and the refinement names link to
%     _hyperchunk_N. That anchor is placed in the margin next to the
%     first line of the C part of section N, and therefore it does not
%     exist for a section without C part (pure commentary, or only a
%     definition part). The anchor _hypersect_N at the start of every
%     section always exists.
%
% (3) The list of changed sections at the end ("\ch 60\*, 66\*, 74\*.")
%     is typeset as ONE link whose name is the whole list. Also, cweb-hy
%     sets it as a section "Changed Chunks" of its own, and since the
%     index starts with \twocolumn (new page), the list stands alone on a
%     page. cwebmac sets it as a small note; in POLYNUM it appears at the
%     top of the index page because the last section there is "@* Index."
%     and \inx puts the page-so-far on top of the two-column index.
%
% (4) In the index and in the section numbers after refinement names,
%     the numbers are separated only by spaces ("argc: 102 103* 105*.");
%     CWEB's plain macros (cwebmac) use commas.
%
% (5) In the index, the change flag * takes space before the following
%     comma or period, and at an underlined number (section where the
%     identifier is defined), $\underline{103\*}$, it is a centered math
%     asterisk. cwebmac lets \* be \lapstar = \rlap{*} in the index: the
%     star overlaps the comma or period, and inside the \rlap box it is a
%     raised text asterisk outside the underline.
%
% (6) In a refinement name <Parse the command line 103\*> the change
%     flag is invisible: there \* has its LaTeX meaning (a discretionary
%     multiplication sign), while cwebmac shows "103*".
%
% (7) In the hierarchic structure, the chunk number is printed only in
%     the margin of the first C part of the chunk (by \B). A chunk with no
%     C part (only commentary and maybe @d definitions) shows its number
%     nowhere, although the index and the links refer to it.
%
% Fix: \hypertarget and \hyperlink delete \* and spaces from the names
% (\cwebhyfix@strip@name); in addition, \hyperlink redirects
% _hyperchunk_N to _hypersect_N (\cwebhyfix@normalize@name). So every
% link to section N, changed or not, with or without C part, goes to the
% start of section N. (The margin anchors _hyperchunk_N stay, but are no
% longer used.) The list of changed sections gets one link per section
% and becomes a line under the heading of the index (\cwebIndexIntro).
% \cweb@num@lnk is redefined to separate the numbers by commas.
% \CwebIndexEntry sets \* to \rlap{*} as in cwebmac. \CwebRefNumber
% shows \* as the change flag. A chunk without C part gets its number in
% the margin at its first line (needs a second LaTeX run, via the .aux).

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{cweb-hy-fix}[2026/11/15 cweb-hy with repaired hyperlinks]
\LoadClassWithOptions{cweb-hy}

% cweb-hy names its macros with underscores (\cweb@changed_list), so _ is
% a letter in this file; restored at the end.
\edef\cwebhyfix@restore@underscore{\catcode`\noexpand\_=\the\catcode`\_\relax}
\catcode`\_=11

% The anchor and link names of cweb-hy, as strings of category 12,
% so that they can be compared with detokenized names.
\edef\cwebhyfix@chunk@prefix{\detokenize{_hyperchunk_}}
\edef\cwebhyfix@section@prefix{\detokenize{_hypersect_}}

% \cwebhyfix@strip@name{name} puts the name without \* and spaces into
% \cwebhyfix@name (globally), as a string of category 12;
% \cwebhyfix@normalize@name{name} also redirects _hyperchunk_. Entry
% condition: the name expands, with \* removed, to a plain string; this
% holds for the names of cweb-hy (prefix and section number) and for
% the usual \hyperlink names.
\def\cwebhyfix@normalize@name#1{%
  \cwebhyfix@strip@name{#1}%
  \edef\cwebhyfix@next{\noexpand\cwebhyfix@redirect@chunk
    \cwebhyfix@name\cwebhyfix@chunk@prefix\noexpand\cwebhyfix@end}%
  \cwebhyfix@next}
\def\cwebhyfix@strip@name#1{%
  \begingroup
    \let\*\@empty
    \xdef\cwebhyfix@name{#1}%
  \endgroup
  \xdef\cwebhyfix@name{%
    \expandafter\zap@space\detokenize\expandafter{\cwebhyfix@name} \@empty}}

% The two macros below are delimited by the category-12 string
% _hyperchunk_, so they are defined via \edef. \cwebhyfix@end is only a
% delimiter and never occurs in names.
% \cwebhyfix@redirect@chunk sees  <name>_hyperchunk_\cwebhyfix@end.
% #1 is the part of the name before its first _hyperchunk_; it is empty
% iff the name starts with _hyperchunk_, and then #2 is the section
% number followed by the appended _hyperchunk_, which
% \cwebhyfix@section@number@of removes.
\begingroup
\edef\x{\endgroup
  \def\noexpand\cwebhyfix@redirect@chunk
      ##1\cwebhyfix@chunk@prefix##2\noexpand\cwebhyfix@end{%
    \noexpand\cwebhyfix@redirect@if@chunk{##1}{##2}}%
  \def\noexpand\cwebhyfix@section@number@of
      ##1\cwebhyfix@chunk@prefix##2\noexpand\cwebhyfix@end{##1}}
\x
\def\cwebhyfix@redirect@if@chunk#1#2{%
  \if\relax\detokenize{#1}\relax   % name starts with _hyperchunk_
    \xdef\cwebhyfix@name{\cwebhyfix@section@prefix
      \cwebhyfix@section@number@of#2\cwebhyfix@end}%
  \fi}

\AtBeginDocument{%
  \let\cwebhyfix@original@hyperlink\hyperlink
  \let\cwebhyfix@original@hypertarget\hypertarget
  \def\hyperlink#1{%
    \cwebhyfix@normalize@name{#1}%
    \expandafter\cwebhyfix@original@hyperlink\expandafter{\cwebhyfix@name}}%
  \def\hypertarget#1{%
    \cwebhyfix@strip@name{#1}%
    \expandafter\cwebhyfix@original@hypertarget\expandafter{\cwebhyfix@name}}%
}

% (3) The list of changed sections. cweave writes "\ch 60\*, 66\*." just
% before the index; cweb-hy lets \ch be \cweb@changed_list when the
% document ends, so redefining \cweb@changed_list here takes effect. It
% only appends the line to \cwebIndexIntro, which \CwebIdIndex typesets
% full width under the heading "Index" (in the optional argument of
% \twocolumn). Hence the list appears only if there is an index.
\def\CwebChangedListText{The following chunks were changed by the change file:}
\if@cweb@suppress@changehints@
\else
  \def\cweb@changed_list#1.{%
    \global\cwebIndexIntro\expandafter{\the\cwebIndexIntro
      \cwebhyfix@changed@line{#1}}}
\fi
% \cwebhyfix@changed@line{60\*, 66\*} links each number separately.
\def\cwebhyfix@changed@line#1{%
  \par\noindent
  {\reset@font\CwebCRSize \CwebChangedListText\space
    \let\*\@empty   % every number here is changed; cwebmac shows no flags
    \let\cwebhyfix@separator\@empty
    \@for\cwebhyfix@section@number:=#1\do{%
      \cwebhyfix@separator\def\cwebhyfix@separator{, }%
      \hyperlink{_hypersect_\cwebhyfix@section@number}%
                {\ignorespaces\cwebhyfix@section@number}}.\par}}

% (4) Commas in number lists. \cweb@num@lnk{list, |} is called by
% cweb-hy for the numbers of an index entry and of a refinement name; the
% list has the form "n1, n2, ..., nk, |", where an item may be \[n]
% (underlined: the identifier is defined in section n) and n may carry
% the change flag \*. Same as the original \cweb@num@lnk in cwbasehy.tex,
% but with ", " instead of a space between the items.
\def\cweb@num@lnk #1, #2|{%
    \begingroup
    \def\[##1]{}%
    \expandafter\def\expandafter\next\expandafter{#1}%
    \ifx\next\empty   % #1 has the form \[n]
        \global\@lbracket@true
    \else
        \global\@lbracket@false
    \fi
    \endgroup
    \if@lbracket@
        \hyper@i#1%
    \else
        \hyperlink{_hyperchunk_#1}{#1}%
    \fi
    \@lbracket@false
    \edef\next{#2}%
    \ifx\next\empty
    \else
        , \cweb@@num@lnk #2|%
    \fi}

% (6) The section numbers of a refinement name, with visible change flag.
% Same as \CwebRefNumber in cwbasehy.tex, plus \let\* (local to the group).
\def\CwebRefNumber#1{%
    {\reset@font \footnotesize \kern .5em\let\*\cwbb@change_flag
     \cweb@num@lnk#1, |}%
    }

% (7) Chunk numbers for chunks without C part (hierarchic structure).
% The original \CwebNumberProgramPart (set up by \cwbb@init_print_chunk
% at each chunk start, called by the first \B of the chunk) puts the
% number in the margin. We record whether it was called; when the next
% chunk starts or the document ends, a chunk where it was not called is
% written to the .aux file as \cwebhyfix@chunk@without@program{N}. In
% the next run, such a chunk puts its number in the margin of its first
% paragraph: the run-in heading line of an unstarred chunk, the heading
% line of a starred one (LaTeX hook para/begin).
% Invariant: \cwebhyfix@previous@chunk is the number of the chunk being
% typeset (empty before the first one), and \ifcwebhyfix@program@part@seen
% says whether this chunk has printed its number at a C part so far.
\ifcase\cweb@structure  % hierarchic
  \newif\ifcwebhyfix@program@part@seen
  \newif\ifcwebhyfix@number@at@paragraph@start
  \def\cwebhyfix@previous@chunk{}
  \def\cwebhyfix@chunk@without@program#1{%
    \global\@namedef{cwebhyfix@without@program@#1}{}}
  \def\cwebhyfix@close@previous@chunk{%
    \ifx\cwebhyfix@previous@chunk\@empty\else
      \ifcwebhyfix@program@part@seen\else
        \immediate\write\@auxout{\string\cwebhyfix@chunk@without@program
          {\cwebhyfix@previous@chunk}}%
      \fi
    \fi}
  \let\cwebhyfix@original@init@print@chunk\cwbb@init_print_chunk
  \def\cwbb@init_print_chunk{%
    \cwebhyfix@close@previous@chunk
    \xdef\cwebhyfix@previous@chunk{\the\c@chunk}%
    \global\cwebhyfix@program@part@seenfalse
    \cwebhyfix@original@init@print@chunk
    % the original defined \CwebNumberProgramPart; record its first call
    \let\cwebhyfix@original@number@program@part\CwebNumberProgramPart
    \def\CwebNumberProgramPart{%
      \global\cwebhyfix@program@part@seentrue
      \cwebhyfix@original@number@program@part}%
    \@ifundefined{cwebhyfix@without@program@\the\c@chunk}%
      {\global\cwebhyfix@number@at@paragraph@startfalse}%
      {\global\cwebhyfix@number@at@paragraph@starttrue}}
  % The margin number is built like \cwbb@marginal_chunkno of cwbasehy,
  % with two differences: \normalfont, because the paragraph may start
  % inside the bold run-in heading; and \everypar{} for the \noindent in
  % the zero-width \vbox, because \everypar may still hold the run-in
  % heading (the pilcrow) of \@startsection, which would otherwise be typeset there
  % (above the line) instead of in the paragraph.
  \AddToHook{para/begin}{%
    \ifcwebhyfix@number@at@paragraph@start
      \global\cwebhyfix@number@at@paragraph@startfalse
      \vadjust{%
        \setbox\z@\hbox to\z@{%
          \hss\vphantom{g}\normalfont\small\thechunk\hskip\marginparsep}%
        \vbox to\z@{%
          \hsize\z@ \vss \everypar{}%
          \noindent\raise\dp\z@\box\z@}}%
    \fi}
  \AtEndDocument{\cwebhyfix@close@previous@chunk}
\fi

% (5) An index entry; same as \CwebIndexEntry in cweb-hy.cls, but with
% the change flag in an \rlap (\cwbb@lap_change_flag, as cwebmac's
% \lapstar). The \let is local to the index, which binds \* anyway.
\def\CwebIndexEntry#1, #2.{%
    \par
    \hangindent\CwebNumberListHangindent
    \leavevmode
    \let\*\cwbb@lap_change_flag
    \cwbb@check_dot{#1}:\quad\cweb@num@lnk#2, |.
    }

\cwebhyfix@restore@underscore
\endinput
