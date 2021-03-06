#include <QtGui>

#include "qhexedit_p.h"
#include "commands.h"
#include "NumericalConstants.h"
#include "StringConstants.h"
#include <QDrag>
#include "../common/IScaObject.h"
#include "../common/IScaObjectFile.h"
#include "../common/IScaObjectTextBlock.h"
#include "../common/IScaObjectDirectory.h"
#include "../common/IScaObjectSymbol.h"
#include "../common/IScaObjectLine.h"
#include "../common/IScaObjectIdentifier.h"
#include "../common/IScaObjectBinaryBlock.h"
/*LICENCE
 *GNU LESSER GENERAL PUBLIC LICENSE
     Version 2.1, February 1999

Copyright (C) 1991, 1999 Free Software Foundation, Inc.
51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
Everyone is permitted to copy and distribute verbatim copies
of this license document, but changing it is not allowed.

[This is the first released version of the Lesser GPL.  It also counts
as the successor of the GNU Library Public License, version 2, hence
the version number 2.1.]

          Preamble

The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
Licenses are intended to guarantee your freedom to share and change
free software--to make sure the software is free for all its users.

This license, the Lesser General Public License, applies to some
specially designated software packages--typically libraries--of the
Free Software Foundation and other authors who decide to use it.  You
can use it too, but we suggest you first think carefully about whether
this license or the ordinary General Public License is the better
strategy to use in any particular case, based on the explanations below.

When we speak of free software, we are referring to freedom of use,
not price.  Our General Public Licenses are designed to make sure that
you have the freedom to distribute copies of free software (and charge
for this service if you wish); that you receive source code or can get
it if you want it; that you can change the software and use pieces of
it in new free programs; and that you are informed that you can do
these things.

To protect your rights, we need to make restrictions that forbid
distributors to deny you these rights or to ask you to surrender these
rights.  These restrictions translate to certain responsibilities for
you if you distribute copies of the library or if you modify it.

For example, if you distribute copies of the library, whether gratis
or for a fee, you must give the recipients all the rights that we gave
you.  You must make sure that they, too, receive or can get the source
code.  If you link other code with the library, you must provide
complete object files to the recipients, so that they can relink them
with the library after making changes to the library and recompiling
it.  And you must show them these terms so they know their rights.

We protect your rights with a two-step method: (1) we copyright the
library, and (2) we offer you this license, which gives you legal
permission to copy, distribute and/or modify the library.

To protect each distributor, we want to make it very clear that
there is no warranty for the free library.  Also, if the library is
modified by someone else and passed on, the recipients should know
that what they have is not the original version, so that the original
author's reputation will not be affected by problems that might be
introduced by others.

Finally, software patents pose a constant threat to the existence of
any free program.  We wish to make sure that a company cannot
effectively restrict the users of a free program by obtaining a
restrictive license from a patent holder.  Therefore, we insist that
any patent license obtained for a version of the library must be
consistent with the full freedom of use specified in this license.

Most GNU software, including some libraries, is covered by the
ordinary GNU General Public License.  This license, the GNU Lesser
General Public License, applies to certain designated libraries, and
is quite different from the ordinary General Public License.  We use
this license for certain libraries in order to permit linking those
libraries into non-free programs.

When a program is linked with a library, whether statically or using
a shared library, the combination of the two is legally speaking a
combined work, a derivative of the original library.  The ordinary
General Public License therefore permits such linking only if the
entire combination fits its criteria of freedom.  The Lesser General
Public License permits more lax criteria for linking other code with
the library.

We call this license the "Lesser" General Public License because it
does Less to protect the user's freedom than the ordinary General
Public License.  It also provides other free software developers Less
of an advantage over competing non-free programs.  These disadvantages
are the reason we use the ordinary General Public License for many
libraries.  However, the Lesser license provides advantages in certain
special circumstances.

For example, on rare occasions, there may be a special need to
encourage the widest possible use of a certain library, so that it becomes
a de-facto standard.  To achieve this, non-free programs must be
allowed to use the library.  A more frequent case is that a free
library does the same job as widely used non-free libraries.  In this
case, there is little to gain by limiting the free library to free
software only, so we use the Lesser General Public License.

In other cases, permission to use a particular library in non-free
programs enables a greater number of people to use a large body of
free software.  For example, permission to use the GNU C Library in
non-free programs enables many more people to use the whole GNU
operating system, as well as its variant, the GNU/Linux operating
system.

Although the Lesser General Public License is Less protective of the
users' freedom, it does ensure that the user of a program that is
linked with the Library has the freedom and the wherewithal to run
that program using a modified version of the Library.

The precise terms and conditions for copying, distribution and
modification follow.  Pay close attention to the difference between a
"work based on the library" and a "work that uses the library".  The
former contains code derived from the library, whereas the latter must
be combined with the library in order to run.

GNU LESSER GENERAL PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

0. This License Agreement applies to any software library or other
program which contains a notice placed by the copyright holder or
other authorized party saying it may be distributed under the terms of
this Lesser General Public License (also called "this License").
Each licensee is addressed as "you".

A "library" means a collection of software functions and/or data
prepared so as to be conveniently linked with application programs
(which use some of those functions and data) to form executables.

The "Library", below, refers to any such software library or work
which has been distributed under these terms.  A "work based on the
Library" means either the Library or any derivative work under
copyright law: that is to say, a work containing the Library or a
portion of it, either verbatim or with modifications and/or translated
straightforwardly into another language.  (Hereinafter, translation is
included without limitation in the term "modification".)

"Source code" for a work means the preferred form of the work for
making modifications to it.  For a library, complete source code means
all the source code for all modules it contains, plus any associated
interface definition files, plus the scripts used to control compilation
and installation of the library.

Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running a program using the Library is not restricted, and output from
such a program is covered only if its contents constitute a work based
on the Library (independent of the use of the Library in a tool for
writing it).  Whether that is true depends on what the Library does
and what the program that uses the Library does.

1. You may copy and distribute verbatim copies of the Library's
complete source code as you receive it, in any medium, provided that
you conspicuously and appropriately publish on each copy an
appropriate copyright notice and disclaimer of warranty; keep intact
all the notices that refer to this License and to the absence of any
warranty; and distribute a copy of this License along with the
Library.

You may charge a fee for the physical act of transferring a copy,
and you may at your option offer warranty protection in exchange for a
fee.

2. You may modify your copy or copies of the Library or any portion
of it, thus forming a work based on the Library, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions:

a) The modified work must itself be a software library.

b) You must cause the files modified to carry prominent notices
stating that you changed the files and the date of any change.

c) You must cause the whole of the work to be licensed at no
charge to all third parties under the terms of this License.

d) If a facility in the modified Library refers to a function or a
table of data to be supplied by an application program that uses
the facility, other than as an argument passed when the facility
is invoked, then you must make a good faith effort to ensure that,
in the event an application does not supply such function or
table, the facility still operates, and performs whatever part of
its purpose remains meaningful.

(For example, a function in a library to compute square roots has
a purpose that is entirely well-defined independent of the
application.  Therefore, Subsection 2d requires that any
application-supplied function or table used by this function must
be optional: if the application does not supply it, the square
root function must still compute square roots.)

These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Library,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Library, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote
it.

Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Library.

In addition, mere aggregation of another work not based on the Library
with the Library (or with a work based on the Library) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

3. You may opt to apply the terms of the ordinary GNU General Public
License instead of this License to a given copy of the Library.  To do
this, you must alter all the notices that refer to this License, so
that they refer to the ordinary GNU General Public License, version 2,
instead of to this License.  (If a newer version than version 2 of the
ordinary GNU General Public License has appeared, then you can specify
that version instead if you wish.)  Do not make any other change in
these notices.

Once this change is made in a given copy, it is irreversible for
that copy, so the ordinary GNU General Public License applies to all
subsequent copies and derivative works made from that copy.

This option is useful when you wish to copy part of the code of
the Library into a program that is not a library.

4. You may copy and distribute the Library (or a portion or
derivative of it, under Section 2) in object code or executable form
under the terms of Sections 1 and 2 above provided that you accompany
it with the complete corresponding machine-readable source code, which
must be distributed under the terms of Sections 1 and 2 above on a
medium customarily used for software interchange.

If distribution of object code is made by offering access to copy
from a designated place, then offering equivalent access to copy the
source code from the same place satisfies the requirement to
distribute the source code, even though third parties are not
compelled to copy the source along with the object code.

5. A program that contains no derivative of any portion of the
Library, but is designed to work with the Library by being compiled or
linked with it, is called a "work that uses the Library".  Such a
work, in isolation, is not a derivative work of the Library, and
therefore falls outside the scope of this License.

However, linking a "work that uses the Library" with the Library
creates an executable that is a derivative of the Library (because it
contains portions of the Library), rather than a "work that uses the
library".  The executable is therefore covered by this License.
Section 6 states terms for distribution of such executables.

When a "work that uses the Library" uses material from a header file
that is part of the Library, the object code for the work may be a
derivative work of the Library even though the source code is not.
Whether this is true is especially significant if the work can be
linked without the Library, or if the work is itself a library.  The
threshold for this to be true is not precisely defined by law.

If such an object file uses only numerical parameters, data
structure layouts and accessors, and small macros and small inline
functions (ten lines or less in length), then the use of the object
file is unrestricted, regardless of whether it is legally a derivative
work.  (Executables containing this object code plus portions of the
Library will still fall under Section 6.)

Otherwise, if the work is a derivative of the Library, you may
distribute the object code for the work under the terms of Section 6.
Any executables containing that work also fall under Section 6,
whether or not they are linked directly with the Library itself.

6. As an exception to the Sections above, you may also combine or
link a "work that uses the Library" with the Library to produce a
work containing portions of the Library, and distribute that work
under terms of your choice, provided that the terms permit
modification of the work for the customer's own use and reverse
engineering for debugging such modifications.

You must give prominent notice with each copy of the work that the
Library is used in it and that the Library and its use are covered by
this License.  You must supply a copy of this License.  If the work
during execution displays copyright notices, you must include the
copyright notice for the Library among them, as well as a reference
directing the user to the copy of this License.  Also, you must do one
of these things:

a) Accompany the work with the complete corresponding
machine-readable source code for the Library including whatever
changes were used in the work (which must be distributed under
Sections 1 and 2 above); and, if the work is an executable linked
with the Library, with the complete machine-readable "work that
uses the Library", as object code and/or source code, so that the
user can modify the Library and then relink to produce a modified
executable containing the modified Library.  (It is understood
that the user who changes the contents of definitions files in the
Library will not necessarily be able to recompile the application
to use the modified definitions.)

b) Use a suitable shared library mechanism for linking with the
Library.  A suitable mechanism is one that (1) uses at run time a
copy of the library already present on the user's computer system,
rather than copying library functions into the executable, and (2)
will operate properly with a modified version of the library, if
the user installs one, as long as the modified version is
interface-compatible with the version that the work was made with.

c) Accompany the work with a written offer, valid for at
least three years, to give the same user the materials
specified in Subsection 6a, above, for a charge no more
than the cost of performing this distribution.

d) If distribution of the work is made by offering access to copy
from a designated place, offer equivalent access to copy the above
specified materials from the same place.

e) Verify that the user has already received a copy of these
materials or that you have already sent this user a copy.

For an executable, the required form of the "work that uses the
Library" must include any data and utility programs needed for
reproducing the executable from it.  However, as a special exception,
the materials to be distributed need not include anything that is
normally distributed (in either source or binary form) with the major
components (compiler, kernel, and so on) of the operating system on
which the executable runs, unless that component itself accompanies
the executable.

It may happen that this requirement contradicts the license
restrictions of other proprietary libraries that do not normally
accompany the operating system.  Such a contradiction means you cannot
use both them and the Library together in an executable that you
distribute.

7. You may place library facilities that are a work based on the
Library side-by-side in a single library together with other library
facilities not covered by this License, and distribute such a combined
library, provided that the separate distribution of the work based on
the Library and of the other library facilities is otherwise
permitted, and provided that you do these two things:

a) Accompany the combined library with a copy of the same work
based on the Library, uncombined with any other library
facilities.  This must be distributed under the terms of the
Sections above.

b) Give prominent notice with the combined library of the fact
that part of it is a work based on the Library, and explaining
where to find the accompanying uncombined form of the same work.

8. You may not copy, modify, sublicense, link with, or distribute
the Library except as expressly provided under this License.  Any
attempt otherwise to copy, modify, sublicense, link with, or
distribute the Library is void, and will automatically terminate your
rights under this License.  However, parties who have received copies,
or rights, from you under this License will not have their licenses
terminated so long as such parties remain in full compliance.

9. You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Library or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Library (or any work based on the
Library), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Library or works based on it.

10. Each time you redistribute the Library (or any work based on the
Library), the recipient automatically receives a license from the
original licensor to copy, distribute, link with or modify the Library
subject to these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties with
this License.

11. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Library at all.  For example, if a patent
license would not permit royalty-free redistribution of the Library by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Library.

If any portion of this section is held invalid or unenforceable under any
particular circumstance, the balance of the section is intended to apply,
and the section as a whole is intended to apply in other circumstances.

It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.

This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.

12. If the distribution and/or use of the Library is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Library under this License may add
an explicit geographical distribution limitation excluding those countries,
so that distribution is permitted only in or among countries not thus
excluded.  In such case, this License incorporates the limitation as if
written in the body of this License.

13. The Free Software Foundation may publish revised and/or new
versions of the Lesser General Public License from time to time.
Such new versions will be similar in spirit to the present version,
but may differ in detail to address new problems or concerns.

Each version is given a distinguishing version number.  If the Library
specifies a version number of this License which applies to it and
"any later version", you have the option of following the terms and
conditions either of that version or of any later version published by
the Free Software Foundation.  If the Library does not specify a
license version number, you may choose any version ever published by
the Free Software Foundation.

14. If you wish to incorporate parts of the Library into other free
programs whose distribution conditions are incompatible with these,
write to the author to ask for permission.  For software which is
copyrighted by the Free Software Foundation, write to the Free
Software Foundation; we sometimes make exceptions for this.  Our
decision will be guided by the two goals of preserving the free status
of all derivatives of our free software and of promoting the sharing
and reuse of software generally.

          NO WARRANTY

15. BECAUSE THE LIBRARY IS LICENSED FREE OF CHARGE, THERE IS NO
WARRANTY FOR THE LIBRARY, TO THE EXTENT PERMITTED BY APPLICABLE LAW.
EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR
OTHER PARTIES PROVIDE THE LIBRARY "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
LIBRARY IS WITH YOU.  SHOULD THE LIBRARY PROVE DEFECTIVE, YOU ASSUME
THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

16. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN
WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY
AND/OR REDISTRIBUTE THE LIBRARY AS PERMITTED ABOVE, BE LIABLE TO YOU
FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE
LIBRARY (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING
RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A
FAILURE OF THE LIBRARY TO OPERATE WITH ANY OTHER SOFTWARE), EVEN IF
SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGES.

   END OF TERMS AND CONDITIONS

How to Apply These Terms to Your New Libraries

If you develop a new library, and you want it to be of the greatest
possible use to the public, we recommend making it free software that
everyone can redistribute and change.  You can do so by permitting
redistribution under these terms (or, alternatively, under the terms of the
ordinary General Public License).

To apply these terms, attach the following notices to the library.  It is
safest to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least the
"copyright" line and a pointer to where the full notice is found.

<one line to give the library's name and a brief idea of what it does.>
Copyright (C) <year>  <name of author>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Also add information on how to contact you by electronic and paper mail.

You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the library, if
necessary.  Here is a sample; alter the names:

Yoyodyne, Inc., hereby disclaims all copyright interest in the
library `Frob' (a library for tweaking knobs) written by James Random Hacker.

<signature of Ty Coon>, 1 April 1990
Ty Coon, President of Vice

That's all there is to it!/*/
QHexEditPrivate::QHexEditPrivate(QScrollArea *parent) : QWidget(parent)
{
    _undoStack = new QUndoStack(this);

    _draggingOut = false;
    _scrollArea = parent;
    setAddressWidth(4);
    setAddressOffset(0);
    setAddressArea(true);
    setAsciiArea(true);
    setHighlighting(true);
    setOverwriteMode(true);
    setReadOnly(false);
    setAddressAreaColor(QColor(0xd4, 0xd4, 0xd4, 0xff));
    setHighlightingColor(QColor(0xff, 0xff, 0x99, 0xff));
    setSelectionColor(QColor(0x6d, 0x9e, 0xff, 0xff));
    setFont(QFont("Courier", 10));

    _size = 0;
    resetSelection(0);

    setFocusPolicy(Qt::StrongFocus);

    connect(&_cursorTimer, SIGNAL(timeout()), this, SLOT(updateCursor()));
    _cursorTimer.setInterval(500);
    _cursorTimer.start();
}

void QHexEditPrivate::setAddressOffset(int offset)
{
    _xData.setAddressOffset(offset);
    adjust();
}

int QHexEditPrivate::addressOffset()
{
    return _xData.addressOffset();
}

void QHexEditPrivate::setData(const QByteArray &data)
{
    _xData.setData(data);
    _undoStack->clear();
    adjust();
    setCursorPos(0);
}

QByteArray QHexEditPrivate::data()
{
    return _xData.data();
}

QByteArray QHexEditPrivate::getSelectedData()
{
    return _xData.data().mid(getSelectionBegin(), getSelectionEnd() - getSelectionBegin());
}

void QHexEditPrivate::setAddressAreaColor(const QColor &color)
{
    _addressAreaColor = color;
    update();
}

QColor QHexEditPrivate::addressAreaColor()
{
    return _addressAreaColor;
}

void QHexEditPrivate::setHighlightingColor(const QColor &color)
{
    _highlightingColor = color;
    update();
}

QColor QHexEditPrivate::highlightingColor()
{
    return _highlightingColor;
}

void QHexEditPrivate::setSelectionColor(const QColor &color)
{
    _selectionColor = color;
    update();
}

QColor QHexEditPrivate::selectionColor()
{
    return _selectionColor;
}

void QHexEditPrivate::setReadOnly(bool readOnly)
{
    _readOnly = readOnly;
}

bool QHexEditPrivate::isReadOnly()
{
    return _readOnly;
}

XByteArray & QHexEditPrivate::xData()
{
    return _xData;
}

int QHexEditPrivate::indexOf(const QByteArray & ba, int from)
{
    if (from > (_xData.data().length() - 1))
        from = _xData.data().length() - 1;
    int idx = _xData.data().indexOf(ba, from);
    if (idx > -1)
    {
        int curPos = idx*2;
        setCursorPos(curPos + ba.length()*2);
        resetSelection(curPos);
        setSelection(curPos + ba.length()*2);
        ensureVisible();
    }
    return idx;
}

void QHexEditPrivate::insert(int index, const QByteArray & ba)
{
    if (ba.length() > 0)
    {
        if (_overwriteMode)
        {
            QUndoCommand *arrayCommand= new ArrayCommand(&_xData, ArrayCommand::replace, index, ba, ba.length());
            _undoStack->push(arrayCommand);
            emit dataChanged();
        }
        else
        {
            QUndoCommand *arrayCommand= new ArrayCommand(&_xData, ArrayCommand::insert, index, ba, ba.length());
            _undoStack->push(arrayCommand);
            emit dataChanged();
        }
    }
}

void QHexEditPrivate::insert(int index, char ch)
{
    QUndoCommand *charCommand = new CharCommand(&_xData, CharCommand::insert, index, ch);
    _undoStack->push(charCommand);
    emit dataChanged();
}

int QHexEditPrivate::lastIndexOf(const QByteArray & ba, int from)
{
    from -= ba.length();
    if (from < 0)
        from = 0;
    int idx = _xData.data().lastIndexOf(ba, from);
    if (idx > -1)
    {
        int curPos = idx*2;
        setCursorPos(curPos);
        resetSelection(curPos);
        setSelection(curPos + ba.length()*2);
        ensureVisible();
    }
    return idx;
}

void QHexEditPrivate::remove(int index, int len)
{
    if (len > 0)
    {
        if (len == 1)
        {
            if (_overwriteMode)
            {
                QUndoCommand *charCommand = new CharCommand(&_xData, CharCommand::replace, index, char(0));
                _undoStack->push(charCommand);
                emit dataChanged();
            }
            else
            {
                QUndoCommand *charCommand = new CharCommand(&_xData, CharCommand::remove, index, char(0));
                _undoStack->push(charCommand);
                emit dataChanged();
            }
        }
        else
        {
            QByteArray ba = QByteArray(len, char(0));
            if (_overwriteMode)
            {
                QUndoCommand *arrayCommand = new ArrayCommand(&_xData, ArrayCommand::replace, index, ba, ba.length());
                _undoStack->push(arrayCommand);
                emit dataChanged();
            }
            else
            {
                QUndoCommand *arrayCommand= new ArrayCommand(&_xData, ArrayCommand::remove, index, ba, len);
                _undoStack->push(arrayCommand);
                emit dataChanged();
            }
        }
    }
}

void QHexEditPrivate::replace(int index, char ch)
{
    QUndoCommand *charCommand = new CharCommand(&_xData, CharCommand::replace, index, ch);
    _undoStack->push(charCommand);
    resetSelection();
    emit dataChanged();
}

void QHexEditPrivate::replace(int index, const QByteArray & ba)
{
    QUndoCommand *arrayCommand= new ArrayCommand(&_xData, ArrayCommand::replace, index, ba, ba.length());
    _undoStack->push(arrayCommand);
    resetSelection();
    emit dataChanged();
}

void QHexEditPrivate::replace(int pos, int len, const QByteArray &after)
{
    QUndoCommand *arrayCommand= new ArrayCommand(&_xData, ArrayCommand::replace, pos, after, len);
    _undoStack->push(arrayCommand);
    resetSelection();
    emit dataChanged();
}

void QHexEditPrivate::setAddressArea(bool addressArea)
{
    _addressArea = addressArea;
    adjust();

    setCursorPos(_cursorPosition);
}

void QHexEditPrivate::setAddressWidth(int addressWidth)
{
    _xData.setAddressWidth(addressWidth);

    setCursorPos(_cursorPosition);
}

void QHexEditPrivate::setAsciiArea(bool asciiArea)
{
    _asciiArea = asciiArea;
    adjust();
}

void QHexEditPrivate::setFont(const QFont &font)
{
    QWidget::setFont(font);
    adjust();
}

void QHexEditPrivate::setHighlighting(bool mode)
{
    _highlighting = mode;
    update();
}

void QHexEditPrivate::setOverwriteMode(bool overwriteMode)
{
    _overwriteMode = overwriteMode;
}

bool QHexEditPrivate::overwriteMode()
{
    return _overwriteMode;
}

void QHexEditPrivate::redo()
{
    _undoStack->redo();
    emit dataChanged();
    setCursorPos(_cursorPosition);
    update();
}

void QHexEditPrivate::undo()
{
    _undoStack->undo();
    emit dataChanged();
    setCursorPos(_cursorPosition);
    update();
}

QString QHexEditPrivate::toReadableString()
{
    return _xData.toReadableString();
}


QString QHexEditPrivate::selectionToReadableString()
{
    return _xData.toReadableString(getSelectionBegin(), getSelectionEnd());
}

void QHexEditPrivate::goToBinaryBlock(IScaObjectBinaryBlock *obj)
{
    setCursorPos(obj->getOffset() * 2);
    int offset = obj->getOffset() * 2;
    int endOffset = offset + obj->getLength() * 2;
    resetSelection(offset);
    setSelection(endOffset);
    ensureVisible();
}

void QHexEditPrivate::goToTextBlock(IScaObjectTextBlock *obj)
{
    setCursorPos(obj->getOffset());
    int offset = obj->getOffset() * 2;
    int endOffset = offset + obj->getLength() * 2;
    resetSelection(offset);
    setSelection(endOffset);
    ensureVisible();
}

void QHexEditPrivate::goToIdentifier(IScaObjectIdentifier *obj)
{
    setCursorPos(obj->getOffset());
    int offset = obj->getOffset() * 2;
    int endOffset = obj->getEndOffset() * 2;
    resetSelection(offset);
    setSelection(endOffset);
    ensureVisible();
}

void QHexEditPrivate::goToSymbol(IScaObjectSymbol *obj)
{
    setCursorPos(obj->getOffset());
    int offset = obj->getOffset() * 2;
    int endOffset = offset + 2;
    resetSelection(offset);
    setSelection(endOffset);
    ensureVisible();
}

void QHexEditPrivate::goToLine(IScaObjectLine *obj)
{
    setCursorPos(obj->getOffset());
    int offset = obj->getOffset() * 2;
    int endOffset = obj->getEndOffset() * 2;
    resetSelection(offset);
    setSelection(endOffset);
    ensureVisible();
}

void QHexEditPrivate::keyPressEvent(QKeyEvent *event)
{
    int charX = (_cursorX - _xPosHex) / _charWidth;
    int posX = (charX / 3) * 2 + (charX % 3);
    int posBa = (_cursorY / _charHeight) * BYTES_PER_LINE + posX / 2;


    /*****************************************************************************/
    /* Cursor movements */
    /*****************************************************************************/

    if (event->matches(QKeySequence::MoveToNextChar))
    {
        setCursorPos(_cursorPosition + 1);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousChar))
    {
        setCursorPos(_cursorPosition - 1);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToEndOfLine))
    {
        setCursorPos(_cursorPosition | (2 * BYTES_PER_LINE -1));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToStartOfLine))
    {
        setCursorPos(_cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE)));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousLine))
    {
        setCursorPos(_cursorPosition - (2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToNextLine))
    {
        setCursorPos(_cursorPosition + (2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }

    if (event->matches(QKeySequence::MoveToNextPage))
    {
        setCursorPos(_cursorPosition + (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousPage))
    {
        setCursorPos(_cursorPosition - (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToEndOfDocument))
    {
        setCursorPos(_xData.size() * 2);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToStartOfDocument))
    {
        setCursorPos(0);
        resetSelection(_cursorPosition);
    }

    /*****************************************************************************/
    /* Select commands */
    /*****************************************************************************/
    if (event->matches(QKeySequence::SelectAll))
    {
        resetSelection(0);
        setSelection(2*_xData.size() + 1);
    }
    if (event->matches(QKeySequence::SelectNextChar))
    {
        int pos = _cursorPosition + 1;
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousChar))
    {
        int pos = _cursorPosition - 1;
        setSelection(pos);
        setCursorPos(pos);
    }
    if (event->matches(QKeySequence::SelectEndOfLine))
    {
        int pos = _cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE)) + (2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectStartOfLine))
    {
        int pos = _cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE));
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousLine))
    {
        int pos = _cursorPosition - (2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectNextLine))
    {
        int pos = _cursorPosition + (2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }

    if (event->matches(QKeySequence::SelectNextPage))
    {
        int pos = _cursorPosition + (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousPage))
    {
        int pos = _cursorPosition - (((_scrollArea->viewport()->height() / _charHeight) - 1) * 2 * BYTES_PER_LINE);
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectEndOfDocument))
    {
        int pos = _xData.size() * 2;
        setCursorPos(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectStartOfDocument))
    {
        int pos = 0;
        setCursorPos(pos);
        setSelection(pos);
    }
    if(event->key() == Qt::Key_S)
    {

    }

    /*****************************************************************************/
    /* Edit Commands */
    /*****************************************************************************/
    if (!_readOnly)
    {
        /* Hex input */
        int key = int(event->text()[0].toAscii());
        if ((key>='0' && key<='9') || (key>='a' && key <= 'f'))
        {
            if (getSelectionBegin() != getSelectionEnd())
            {
                posBa = getSelectionBegin();
                remove(posBa, getSelectionEnd() - posBa);
                setCursorPos(2*posBa);
                resetSelection(2*posBa);
            }

            // If insert mode, then insert a byte
            if (_overwriteMode == false)
                if ((charX % 3) == 0)
                {
                    insert(posBa, char(0));
                }

            // Change content
            if (_xData.size() > 0)
            {
                QByteArray hexValue = _xData.data().mid(posBa, 1).toHex();
                if ((charX % 3) == 0)
                    hexValue[0] = key;
                else
                    hexValue[1] = key;

                replace(posBa, QByteArray().fromHex(hexValue)[0]);

                setCursorPos(_cursorPosition + 1);
                resetSelection(_cursorPosition);
            }
        }

        /* Cut & Paste */
        if (event->matches(QKeySequence::Cut))
        {
            QString result = QString();
            for (int idx = getSelectionBegin(); idx < getSelectionEnd(); idx++)
            {
                result += _xData.data().mid(idx, 1).toHex() + " ";
                if ((idx % 16) == 15)
                    result.append("\n");
            }
            remove(getSelectionBegin(), getSelectionEnd() - getSelectionBegin());
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(result);
            setCursorPos(getSelectionBegin());
            resetSelection(getSelectionBegin());
        }

        if (event->matches(QKeySequence::Paste))
        {
            QClipboard *clipboard = QApplication::clipboard();
            QByteArray ba = QByteArray().fromHex(clipboard->text().toLatin1());
            insert(_cursorPosition / 2, ba);
            setCursorPos(_cursorPosition + 2 * ba.length());
            resetSelection(getSelectionBegin());
        }


        /* Delete char */
        if (event->matches(QKeySequence::Delete))
        {
            if (getSelectionBegin() != getSelectionEnd())
            {
                posBa = getSelectionBegin();
                remove(posBa, getSelectionEnd() - posBa);
                setCursorPos(2*posBa);
                resetSelection(2*posBa);
            }
            else
            {
                if (_overwriteMode)
                    replace(posBa, char(0));
                else
                    remove(posBa, 1);
            }
        }

        /* Backspace */
        if ((event->key() == Qt::Key_Backspace) && (event->modifiers() == Qt::NoModifier))
        {
            if (getSelectionBegin() != getSelectionEnd())
            {
                posBa = getSelectionBegin();
                remove(posBa, getSelectionEnd() - posBa);
                setCursorPos(2*posBa);
                resetSelection(2*posBa);
            }
            else
            {
                if (posBa > 0)
                {
                    if (_overwriteMode)
                        replace(posBa - 1, char(0));
                    else
                        remove(posBa - 1, 1);
                    setCursorPos(_cursorPosition - 2);
                }
            }
        }

        /* undo */
        if (event->matches(QKeySequence::Undo))
        {
            undo();
        }

        /* redo */
        if (event->matches(QKeySequence::Redo))
        {
            redo();
        }

    }

    if (event->matches(QKeySequence::Copy))
    {
        QString result = QString();
        for (int idx = getSelectionBegin(); idx < getSelectionEnd(); idx++)
        {
            result += _xData.data().mid(idx, 1).toHex() + " ";
            if ((idx % 16) == 15)
                result.append('\n');
        }
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(result);
    }

    // Switch between insert/overwrite mode
    if ((event->key() == Qt::Key_Insert) && (event->modifiers() == Qt::NoModifier))
    {
        _overwriteMode = !_overwriteMode;
        setCursorPos(_cursorPosition);
        overwriteModeChanged(_overwriteMode);
    }

    ensureVisible();
    update();
}

void QHexEditPrivate::mouseMoveEvent(QMouseEvent * event)
{
    _blink = false;
    update();
    int actPos = cursorPos(event->pos());

    if(_draggingOut)
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = createMimeDataFromSelection();
        drag->setMimeData(mimeData);
        drag->exec(Qt::CopyAction);
    }
    else
    {
        setCursorPos(actPos);
        setSelection(actPos);
    }
}

void QHexEditPrivate::mousePressEvent(QMouseEvent * event)
{
    _blink = false;
    update();
    int cPos = cursorPos(event->pos());
    if(cPos/2 >= getSelectionBegin() && cPos/2 <= getSelectionEnd()
            && (getSelectionBegin() != getSelectionEnd()))
    {
        _draggingOut = true;
    }
    else
    {
        resetSelection(cPos);
        setCursorPos(cPos);
        _draggingOut = false;
    }
}

void QHexEditPrivate::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    _draggingOut = false;
}

void QHexEditPrivate::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // draw some patterns if needed
    painter.fillRect(event->rect(), this->palette().color(QPalette::Base));
    if (_addressArea)
        painter.fillRect(QRect(_xPosAdr, event->rect().top(), _xPosHex - GAP_ADR_HEX + 2, height()), _addressAreaColor);
    if (_asciiArea)
    {
        int linePos = _xPosAscii - (GAP_HEX_ASCII / 2);
        painter.setPen(Qt::gray);
        painter.drawLine(linePos, event->rect().top(), linePos, height());
    }

    painter.setPen(this->palette().color(QPalette::WindowText));

    // calc position
    int firstLineIdx = ((event->rect().top()/ _charHeight) - _charHeight) * BYTES_PER_LINE;
    if (firstLineIdx < 0)
        firstLineIdx = 0;
    int lastLineIdx = ((event->rect().bottom() / _charHeight) + _charHeight) * BYTES_PER_LINE;
    if (lastLineIdx > _xData.size())
        lastLineIdx = _xData.size();
    int yPosStart = ((firstLineIdx) / BYTES_PER_LINE) * _charHeight + _charHeight;

    // paint address area
    if (_addressArea)
    {
        for (int lineIdx = firstLineIdx, yPos = yPosStart; lineIdx < lastLineIdx; lineIdx += BYTES_PER_LINE, yPos +=_charHeight)
        {
            QString address = QString("%1")
                    .arg(lineIdx + _xData.addressOffset(), _xData.realAddressNumbers(), 16, QChar('0'));
            painter.drawText(_xPosAdr, yPos, address);
        }
    }

    // paint hex area
    QByteArray hexBa(_xData.data().mid(firstLineIdx, lastLineIdx - firstLineIdx + 1).toHex());
    QBrush highLighted = QBrush(_highlightingColor);
    QPen colHighlighted = QPen(this->palette().color(QPalette::WindowText));
    QBrush selected = QBrush(_selectionColor);
    QPen colSelected = QPen(Qt::white);
    QPen colStandard = QPen(this->palette().color(QPalette::WindowText));

    painter.setBackgroundMode(Qt::TransparentMode);

    for (int lineIdx = firstLineIdx, yPos = yPosStart; lineIdx < lastLineIdx; lineIdx += BYTES_PER_LINE, yPos +=_charHeight)
    {
        QByteArray hex;
        int xPos = _xPosHex;
        for (int colIdx = 0; ((lineIdx + colIdx) < _xData.size() && (colIdx < BYTES_PER_LINE)); colIdx++)
        {
            int posBa = lineIdx + colIdx;
            if ((getSelectionBegin() <= posBa) && (getSelectionEnd() > posBa))
            {
                painter.setBackground(selected);
                painter.setBackgroundMode(Qt::OpaqueMode);
                painter.setPen(colSelected);
            }
            else
            {
                if (_highlighting)
                {
                    // hilight diff bytes
                    painter.setBackground(highLighted);
                    if (_xData.dataChanged(posBa))
                    {
                        painter.setPen(colHighlighted);
                        painter.setBackgroundMode(Qt::OpaqueMode);
                    }
                    else
                    {
                        painter.setPen(colStandard);
                        painter.setBackgroundMode(Qt::TransparentMode);
                    }
                }
            }

            // render hex value
            if (colIdx == 0)
            {
                hex = hexBa.mid((lineIdx - firstLineIdx) * 2, 2);
                painter.drawText(xPos, yPos, hex);
                xPos += 2 * _charWidth;
            } else {
                hex = hexBa.mid((lineIdx + colIdx - firstLineIdx) * 2, 2).prepend(" ");
                painter.drawText(xPos, yPos, hex);
                xPos += 3 * _charWidth;
            }

        }
    }
    painter.setBackgroundMode(Qt::TransparentMode);
    painter.setPen(this->palette().color(QPalette::WindowText));

    // paint ascii area
    if (_asciiArea)
    {
        for (int lineIdx = firstLineIdx, yPos = yPosStart; lineIdx < lastLineIdx; lineIdx += BYTES_PER_LINE, yPos +=_charHeight)
        {
            int xPosAscii = _xPosAscii;
            for (int colIdx = 0; ((lineIdx + colIdx) < _xData.size() && (colIdx < BYTES_PER_LINE)); colIdx++)
            {
                int posBa = lineIdx + colIdx;
                if ((getSelectionBegin() <= posBa) && (getSelectionEnd() > posBa))
                {
                    painter.setBackground(selected);
                    painter.setBackgroundMode(Qt::OpaqueMode);
                    painter.setPen(colSelected);
                }
                else
                {

                    painter.setBackground(highLighted);

                    painter.setPen(colStandard);
                    painter.setBackgroundMode(Qt::TransparentMode);

                }

                painter.drawText(xPosAscii, yPos, _xData.asciiChar(lineIdx + colIdx));
                xPosAscii += _charWidth;
            }
        }
    }

    // paint cursor
    if (_blink && !_readOnly && hasFocus())
    {
        if (_overwriteMode)
            painter.fillRect(_cursorX, _cursorY + _charHeight - 2, _charWidth, 2, this->palette().color(QPalette::WindowText));
        else
            painter.fillRect(_cursorX, _cursorY, 2, _charHeight, this->palette().color(QPalette::WindowText));
    }

    if (_size != _xData.size())
    {
        _size = _xData.size();
        emit currentSizeChanged(_size);
    }
}

QMimeData *QHexEditPrivate::createMimeDataFromSelection()
{
    QMimeData *mime = new QMimeData();

    QByteArray data = _xData.data().mid(getSelectionBegin(), getSelectionEnd() - getSelectionBegin());
    mime->setData(BINARY_DATA, data);

    mime->setProperty("fromPath", getCurrentPath());
    mime->setProperty("position", getSelectionBegin());
    mime->setProperty("length", getSelectionEnd() - getSelectionBegin());

    return mime;
}

void QHexEditPrivate::setCursorPos(int position)
{
    // delete cursor
    _blink = false;
    update();

    // cursor in range?
    if (_overwriteMode)
    {
        if (position > (_xData.size() * 2 - 1))
            position = _xData.size() * 2 - 1;
    } else {
        if (position > (_xData.size() * 2))
            position = _xData.size() * 2;
    }

    if (position < 0)
        position = 0;

    // calc position
    _cursorPosition = position;
    _cursorY = (position / (2 * BYTES_PER_LINE)) * _charHeight + 4;
    int x = (position % (2 * BYTES_PER_LINE));
    _cursorX = (((x / 2) * 3) + (x % 2)) * _charWidth + _xPosHex;

    // immiadately draw cursor
    _blink = true;
    update();
    emit currentAddressChanged(_cursorPosition/2);
}

int QHexEditPrivate::cursorPos(QPoint pos)
{
    int result = -1;
    // find char under cursor
    if ((pos.x() >= _xPosHex) && (pos.x() < (_xPosHex + HEXCHARS_IN_LINE * _charWidth)))
    {
        int x = (pos.x() - _xPosHex) / _charWidth;
        if ((x % 3) == 0)
            x = (x / 3) * 2;
        else
            x = ((x / 3) * 2) + 1;
        int y = ((pos.y() - 3) / _charHeight) * 2 * BYTES_PER_LINE;
        result = x + y;
    }
    return result;
}

int QHexEditPrivate::cursorPos()
{
    return _cursorPosition;
}

void QHexEditPrivate::resetSelection()
{
    _selectionBegin = _selectionInit;
    _selectionEnd = _selectionInit;
}

void QHexEditPrivate::resetSelection(int pos)
{
    if (pos < 0)
        pos = 0;
    pos = pos / 2;
    _selectionInit = pos;
    _selectionBegin = pos;
    _selectionEnd = pos;
}

void QHexEditPrivate::setSelection(int pos)
{
    if (pos < 0)
        pos = 0;
    pos = pos / 2;
    if (pos >= _selectionInit)
    {
        _selectionEnd = pos;
        _selectionBegin = _selectionInit;
    }
    else
    {
        _selectionBegin = pos;
        _selectionEnd = _selectionInit;
    }
}

int QHexEditPrivate::getSelectionBegin()
{
    return _selectionBegin;
}

int QHexEditPrivate::getSelectionEnd()
{
    return _selectionEnd;
}


void QHexEditPrivate::updateCursor()
{
    if (_blink)
        _blink = false;
    else
        _blink = true;
    update(_cursorX, _cursorY, _charWidth, _charHeight);
}

void QHexEditPrivate::adjust()
{
    _charWidth = fontMetrics().width(QLatin1Char('9'));
    _charHeight = fontMetrics().height();

    _xPosAdr = 0;
    if (_addressArea)
        _xPosHex = _xData.realAddressNumbers()*_charWidth + GAP_ADR_HEX;
    else
        _xPosHex = 0;
    _xPosAscii = _xPosHex + HEXCHARS_IN_LINE * _charWidth + GAP_HEX_ASCII;

    // tell QAbstractScrollbar, how big we are
    setMinimumHeight(qMin(QWIDGETSIZE_MAX, ((_xData.size()/16 + 1) * _charHeight) + 5)-1);
    if(_asciiArea)
        setMinimumWidth(_xPosAscii + (BYTES_PER_LINE * _charWidth));
    else
        setMinimumWidth(_xPosHex + HEXCHARS_IN_LINE * _charWidth);

    update();
}

void QHexEditPrivate::ensureVisible()
{
    // scrolls to cursorx, cusory (which are set by setCursorPos)
    // x-margin is 3 pixels, y-margin is half of charHeight
    _scrollArea->ensureVisible(_cursorX, _cursorY + _charHeight/2, 3, _charHeight/2 + 2);
}

QString QHexEditPrivate::getCurrentPath() const
{
    return _currentPath;
}

void QHexEditPrivate::setCurrentPath(const QString &currentPath)
{
    _currentPath = currentPath;
}

void QHexEditPrivate::clearSelection()
{
    _selectionInit = 0;
    _selectionBegin = 0;
    _selectionEnd = 0;
}
