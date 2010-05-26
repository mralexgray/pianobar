//
//  PianoBarController.h
//  pianobar
//
//  Created by Josh Weinberg on 5/13/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    #import <UIKit/UIKit.h>
#else
    #import <AppKit/AppKit.h>
#endif

#import "piano.h"
#import "waitress.h"
#import "settings.h"
#import "player_macosx.h"

@class PPStation, PPTrack, PPPianobarController;

@protocol PPPianobarDelegate <NSObject>
@optional

-(void)pianobarWillLogin:(PPPianobarController *)pianobar;
-(void)pianobarDidLogin:(PPPianobarController *)pianobar;

-(void)pianobar:(PPPianobarController *)pianobar didBeginPlayingTrack:(PPTrack *)track;
-(void)pianobar:(PPPianobarController *)pianobar didBeginPlayingStation:(PPStation *)station;

-(void)pianobar:(PPPianobarController *)pianobar didBeginPlayingSong:(PPTrack *)song DEPRECATED_ATTRIBUTE;
-(void)pianobar:(PPPianobarController *)pianobar didBeginPlayingChannel:(PPStation *)channel DEPRECATED_ATTRIBUTE;

@end

extern NSString *PPPianobarControllerWillLoginNotification;
extern NSString *PPPianobarControllerDidLoginNotification;
extern NSString *PPPianobarControllerDidBeginPlayingSongNotification;
extern NSString *PPPianobarControllerDidBeginPlayingChannelNotification;

@interface PPPianobarController : NSObject {
	PianoHandle_t ph;
    WaitressHandle_t waith;
    BarSettings_t settings;
    PianoStation_t *curStation;
    PianoSong_t *songHistory;
	PianoSong_t *playlist;
    pthread_t playerThread;
    
    
	NSArray *stations;
    
	PPStation *selectedStation;
	PPTrack *nowPlaying;
    
    BOOL paused;
    NSThread * backgroundPlayer;
    struct audioPlayer player;
    
    id <PPPianobarDelegate> delegate;
}

@property (nonatomic, retain) PPStation *selectedStation;
@property (nonatomic, retain) PPTrack *nowPlaying;

@property (nonatomic, retain) NSArray *stations;

@property (nonatomic, assign) BOOL paused;
@property (nonatomic, assign) id <PPPianobarDelegate> delegate;

@property (nonatomic, assign) double volume;

-(NSAttributedString *)nowPlayingAttributedDescription;
-(BOOL)isInPlaybackMode;
-(BOOL)isPlaying;
-(BOOL)isPaused;

- (id)initWithUsername:(NSString*)username andPassword:(NSString*)password;
- (BOOL)login;
- (BOOL)loadStations;
- (void)playStationWithID:(NSString *)stationID;

- (void)stop;

- (IBAction)thumbsUpCurrentSong:(id)sender;
- (IBAction)thumbsDownCurrentSong:(id)sender;
- (IBAction)playPauseCurrentSong:(id)sender;
- (IBAction)playNextSong:(id)sender;

-(IBAction)openInStore:(id)sender;
-(NSArray *)stationsSimilarToArtist:(NSString *)query;
-(NSArray *)stationsSimilarToSong:(NSString *)query;
-(void)createStationForMusicID:(NSString *)musicID;

-(IBAction)openInStore:(id)sender;

// Calls the delegate if possible, and fires the notification
-(void)_willLogin;
-(void)_didLogin;
-(void)_didBeginPlayingTrack:(PPTrack *)track;
-(void)_didBeginPlayingStation:(PPStation *)station;

@end
