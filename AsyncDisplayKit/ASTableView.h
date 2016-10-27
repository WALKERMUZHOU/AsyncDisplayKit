//
//  ASTableView.h
//  AsyncDisplayKit
//
//  Copyright (c) 2014-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//

#import <UIKit/UIKit.h>
#import <AsyncDisplayKit/ASRangeController.h>
#import <AsyncDisplayKit/ASTableViewProtocols.h>
#import <AsyncDisplayKit/ASBaseDefines.h>
#import <AsyncDisplayKit/ASBatchContext.h>

NS_ASSUME_NONNULL_BEGIN

@class ASCellNode;
@protocol ASTableDataSource;
@protocol ASTableDelegate;
@class ASTableNode;

/**
 * Asynchronous UITableView with Intelligent Preloading capabilities.
 *
 * @discussion ASTableView is a true subclass of UITableView, meaning it is pointer-compatible with code that
 * currently uses UITableView
 *
 * The main difference is that asyncDataSource expects -nodeForRowAtIndexPath, an ASCellNode, and
 * the heightForRowAtIndexPath: method is eliminated (as are the performance problems caused by it).
 * This is made possible because ASCellNodes can calculate their own size, and preload ahead of time.
 *
 * @note ASTableNode is strongly recommended over ASTableView.  This class is provided for adoption convenience.
 */
@interface ASTableView : UITableView

/// The corresponding table node, or nil if one does not exist.
@property (nonatomic, weak, readonly) ASTableNode *tableNode;

@property (nonatomic, weak) id<ASTableDelegate>   asyncDelegate;
@property (nonatomic, weak) id<ASTableDataSource> asyncDataSource;

/**
 * Retrieves the node for the row at the given index path.
 */
- (nullable ASCellNode *)nodeForRowAtIndexPath:(NSIndexPath *)indexPath AS_WARN_UNUSED_RESULT;

/**
 * YES to automatically adjust the contentOffset when cells are inserted or deleted "before"
 * visible cells, maintaining the users' visible scroll position. Currently this feature tracks insertions, moves and deletions of
 * cells, but section edits are ignored.
 *
 * default is NO.
 */
@property (nonatomic) BOOL automaticallyAdjustsContentOffset;

/**
 * The number of screens left to scroll before the delegate -tableView:beginBatchFetchingWithContext: is called.
 *
 * Defaults to two screenfuls.
 */
@property (nonatomic, assign) CGFloat leadingScreensForBatching;

@end

@interface ASTableView (Deprecated)

/**
 * Initializer.
 *
 * @param frame A rectangle specifying the initial location and size of the table view in its superview’s coordinates.
 * The frame of the table view changes as table cells are added and deleted.
 *
 * @param style A constant that specifies the style of the table view. See UITableViewStyle for descriptions of valid constants.
 */
- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style ASDISPLAYNODE_DEPRECATED_MSG("Please use ASTableNode instead of ASTableView.");

/**
 * Tuning parameters for a range type in full mode.
 *
 * @param rangeType The range type to get the tuning parameters for.
 *
 * @return A tuning parameter value for the given range type in full mode.
 *
 * @see ASLayoutRangeMode
 * @see ASLayoutRangeType
 */
- (ASRangeTuningParameters)tuningParametersForRangeType:(ASLayoutRangeType)rangeType AS_WARN_UNUSED_RESULT ASDISPLAYNODE_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Set the tuning parameters for a range type in full mode.
 *
 * @param tuningParameters The tuning parameters to store for a range type.
 * @param rangeType The range type to set the tuning parameters for.
 *
 * @see ASLayoutRangeMode
 * @see ASLayoutRangeType
 */
- (void)setTuningParameters:(ASRangeTuningParameters)tuningParameters forRangeType:(ASLayoutRangeType)rangeType ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Tuning parameters for a range type in the specified mode.
 *
 * @param rangeMode The range mode to get the running parameters for.
 * @param rangeType The range type to get the tuning parameters for.
 *
 * @return A tuning parameter value for the given range type in the given mode.
 *
 * @see ASLayoutRangeMode
 * @see ASLayoutRangeType
 */
- (ASRangeTuningParameters)tuningParametersForRangeMode:(ASLayoutRangeMode)rangeMode rangeType:(ASLayoutRangeType)rangeType AS_WARN_UNUSED_RESULT ASDISPLAYNODE_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Set the tuning parameters for a range type in the specified mode.
 *
 * @param tuningParameters The tuning parameters to store for a range type.
 * @param rangeMode The range mode to set the running parameters for.
 * @param rangeType The range type to set the tuning parameters for.
 *
 * @see ASLayoutRangeMode
 * @see ASLayoutRangeType
 */
- (void)setTuningParameters:(ASRangeTuningParameters)tuningParameters forRangeMode:(ASLayoutRangeMode)rangeMode rangeType:(ASLayoutRangeType)rangeType ASDISPLAYNODE_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Similar to -visibleCells.
 *
 * @return an array containing the cell nodes being displayed on screen.
 */
- (NSArray<ASCellNode *> *)visibleNodes AS_WARN_UNUSED_RESULT ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Similar to -indexPathForCell:.
 *
 * @param cellNode a cellNode part of the table view
 *
 * @return an indexPath for this cellNode
 */
- (nullable NSIndexPath *)indexPathForNode:(ASCellNode *)cellNode AS_WARN_UNUSED_RESULT ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Reload everything from scratch, destroying the working range and all cached nodes.
 *
 * @param completion block to run on completion of asynchronous loading or nil. If supplied, the block is run on
 * the main thread.
 * @warning This method is substantially more expensive than UITableView's version.
 */
-(void)reloadDataWithCompletion:(void (^ _Nullable)())completion ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Reload everything from scratch, destroying the working range and all cached nodes.
 *
 * @warning This method is substantially more expensive than UITableView's version.
 */
- (void)reloadData ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Reload everything from scratch entirely on the main thread, destroying the working range and all cached nodes.
 *
 * @warning This method is substantially more expensive than UITableView's version and will block the main thread while
 * all the cells load.
 */
- (void)reloadDataImmediately ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode's reloadDataWithCompletion: followed by ASTableNode's -waitUntilAllUpdatesAreCommitted instead.");

/**
 * Triggers a relayout of all nodes.
 *
 * @discussion This method invalidates and lays out every cell node in the table view.
 */
- (void)relayoutItems ASDISPLAYNODE_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 *  Begins a series of method calls that insert, delete, select, or reload rows and sections of the table view, with animation enabled and no completion block.
 *
 *  @discussion You call this method to bracket a series of method calls that ends with endUpdates and that consists of operations
 *  to insert, delete, select, and reload rows and sections of the table view. When you call endUpdates, ASTableView begins animating
 *  the operations simultaneously. It's important to remember that the ASTableView will be processing the updates asynchronously after this call is completed.
 *
 *  @warning This method must be called from the main thread.
 */
- (void)beginUpdates ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode's -performBatchUpdates:completion: instead.");

/**
 *  Concludes a series of method calls that insert, delete, select, or reload rows and sections of the table view, with animation enabled and no completion block.
 *
 *  @discussion You call this method to bracket a series of method calls that begins with beginUpdates and that consists of operations
 *  to insert, delete, select, and reload rows and sections of the table view. When you call endUpdates, ASTableView begins animating
 *  the operations simultaneously. It's important to remember that the ASTableView will be processing the updates asynchronously after this call is completed.
 *
 *  @warning This method is must be called from the main thread.
 */
- (void)endUpdates ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode's -performBatchUpdates:completion: instead.");

/**
 *  Concludes a series of method calls that insert, delete, select, or reload rows and sections of the table view.
 *  You call this method to bracket a series of method calls that begins with beginUpdates and that consists of operations
 *  to insert, delete, select, and reload rows and sections of the table view. When you call endUpdates, ASTableView begins animating
 *  the operations simultaneously. This method is must be called from the main thread. It's important to remember that the ASTableView will
 *  be processing the updates asynchronously after this call and are not guaranteed to be reflected in the ASTableView until
 *  the completion block is executed.
 *
 *  @param animated   NO to disable all animations.
 *  @param completion A completion handler block to execute when all of the operations are finished. This block takes a single
 *                    Boolean parameter that contains the value YES if all of the related animations completed successfully or
 *                    NO if they were interrupted. This parameter may be nil. If supplied, the block is run on the main thread.
 */
- (void)endUpdatesAnimated:(BOOL)animated completion:(void (^ _Nullable)(BOOL completed))completion ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode's -performBatchUpdates:completion: instead.");

/**
 *  Blocks execution of the main thread until all section and row updates are committed. This method must be called from the main thread.
 */
- (void)waitUntilAllUpdatesAreCommitted ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Inserts one or more sections, with an option to animate the insertion.
 *
 * @param sections An index set that specifies the sections to insert.
 *
 * @param animation A constant that indicates how the insertion is to be animated. See UITableViewRowAnimation.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)insertSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Deletes one or more sections, with an option to animate the deletion.
 *
 * @param sections An index set that specifies the sections to delete.
 *
 * @param animation A constant that indicates how the deletion is to be animated. See UITableViewRowAnimation.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)deleteSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Reloads the specified sections using a given animation effect.
 *
 * @param sections An index set that specifies the sections to reload.
 *
 * @param animation A constant that indicates how the reloading is to be animated. See UITableViewRowAnimation.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)reloadSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Moves a section to a new location.
 *
 * @param section The index of the section to move.
 *
 * @param newSection The index that is the destination of the move for the section.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection ASDISPLAYNODE_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Inserts rows at the locations identified by an array of index paths, with an option to animate the insertion.
 *
 * @param indexPaths An array of NSIndexPath objects, each representing a row index and section index that together identify a row.
 *
 * @param animation A constant that indicates how the insertion is to be animated. See UITableViewRowAnimation.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)insertRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Deletes the rows specified by an array of index paths, with an option to animate the deletion.
 *
 * @param indexPaths An array of NSIndexPath objects identifying the rows to delete.
 *
 * @param animation A constant that indicates how the deletion is to be animated. See UITableViewRowAnimation.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)deleteRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Reloads the specified rows using a given animation effect.
 *
 * @param indexPaths An array of NSIndexPath objects identifying the rows to reload.
 *
 * @param animation A constant that indicates how the reloading is to be animated. See UITableViewRowAnimation.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)reloadRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation ASDISPLAYNODE_SOON_DEPRECATED_MSG("Use ASTableNode method instead.");

/**
 * Moves the row at a specified location to a destination location.
 *
 * @param indexPath The index path identifying the row to move.
 *
 * @param newIndexPath The index path that is the destination of the move for the row.
 *
 * @discussion This method must be called from the main thread. The asyncDataSource must be updated to reflect the changes
 * before this method is called.
 */
- (void)moveRowAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath ASDISPLAYNODE_DEPRECATED_MSG("Use ASTableNode method instead.");

/// Deprecated in 2.0. You should not call this method.
- (void)clearContents ASDISPLAYNODE_SOON_DEPRECATED_MSG("You should not call this method directly. Intead, rely on the Interstate State callback methods.");

/// Deprecated in 2.0. You should not call this method.
- (void)clearFetchedData ASDISPLAYNODE_DEPRECATED_MSG("You should not call this method directly. Intead, rely on the Interstate State callback methods.");

@end

ASDISPLAYNODE_SOON_DEPRECATED_MSG("Renamed to ASTableDataSource.")
@protocol ASTableViewDataSource <ASTableDataSource>
@end

ASDISPLAYNODE_SOON_DEPRECATED_MSG("Renamed to ASTableDelegate.")
@protocol ASTableViewDelegate <ASTableDelegate>
@end

NS_ASSUME_NONNULL_END
