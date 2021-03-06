//
//  IDEKit_SrcEditViewFolding.h
//  IDEKit
//
//  Created by Glenn Andreas on Fri Jan 30 2004.
//  Copyright (c) 2004 by Glenn Andreas
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Library General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//  
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Library General Public License for more details.
//  
//  You should have received a copy of the GNU Library General Public
//  License along with this library; if not, write to the Free
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#import <Foundation/Foundation.h>
#import "IDEKit_SrcEditView.h"

@interface IDEKit_SrcEditView(FoldingExtensions)
// collapsing primatives
- (void) collapseRange: (NSRange) range;
- (NSInteger) uncollapseAtIndex: (NSUInteger) offset selectResult: (BOOL) shouldSelect; // returns the length of uncollpased text, or 0 if nothing done

- (NSInteger) megaCollapseSelection: (NSRange) range;
- (IBAction) megaCollapse: (id) sender;
- (IBAction) deepUncollapse: (id) sender;
- (IBAction) collapseSelection: (id) sender;
- (void) foldFromOffset: (NSUInteger) offset;
- (IBAction) megaFold: (id) sender;
- (void) megaFoldSelection: (NSRange) range;
// convert between folded & unfolded - note that the two aren't the inverse of each other because
// of loss of precision going to the folded location
- (NSUInteger) unfoldedLocation: (NSUInteger) offset; // convert from unfolded to folded location
- (NSUInteger) foldedLocation: (NSUInteger) offset; // convert from folded to unfolded
- (NSRange) foldedRange: (NSRange) range;
- (NSRange) unfoldedRange: (NSRange) range;

// line number support (which is tweaked by collapsing) - these are all in "unfolded" coordinates
// so the caller doesn't need to know anything about folding
- (NSRange) nthLineRange: (NSInteger) n;
- (NSInteger) lineNumberFromOffset: (NSUInteger) offset;
- (void) selectNthLine: (NSInteger) line;
// for things that really need to know (like the line number gutter
- (NSInteger) foldedLineNumberFromOffset: (NSUInteger) foldedOffset;
- (NSRange) nthFoldedLineRange: (NSInteger) n;
@end

@interface IDEKit_FoldedTextAttachment : NSTextAttachment {
    NSAttributedString *myCollapsedText;
}
+ (IDEKit_FoldedTextAttachment *) foldedTextAttachmentWithCollapsedText:(NSAttributedString *)collapsedText;
- (id)initWithCollapsedText:(NSAttributedString *)collapsedText;
- (NSAttributedString *) collapsedTextInAttachment;
@end

@interface NSTextAttachment(IDEKit_Collapsing)
- (NSAttributedString *) collapsedTextInAttachmentFixIcons: (BOOL) fixIcons;
@end
@interface NSAttributedString(IDEKit_Collapsing)
- (NSAttributedString *)collapsedTextAtIndex: (NSUInteger) offset; // this may be collapsed, so call uncollapsedString on it
- (NSString *) uncollapsedString;
@end
@interface NSString(IDEKit_Collapsing)
@end
