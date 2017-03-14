How and what each group member contributed:

Sid helped with a lot of the base functionality. He implemented random movemaking as well as a bunch of other core things that we wouldn't have been able to complete the project without (including coming up with the final heuristic we used)! 

I (Arnav) implemented minmaxing, caught some mistakes here and there, and wrote some useful helper methods that would have been super useful if we needed to make the bot any better than it was (they were still useful... but they would have been REALLY useful!)

As for the improvements we made this week, the only real one is a slight change to the heuristic we were using. Before, it would always count moves next to the corner as bad moves. In reality, however, if the corner is already taken, moving next to the corner isn't necessarily a bad move. The reason it was a bad move in the first place is because it opens the corner to getting taken, but if the corner is already taken by someone, then the square next to the corner just becomes another edge and should be scored as such. 

As for what we tried, we had a different heuristic in mind at first that scored individual moves rather than the entire board, but it didn't really fit well with the assignment (and in the end, minmaxing and the capability to do things like alpha-beta pruning even though we didn't implement it are much better improvements than our individual move heuristic).

In the end, it seems we were able to beat ConstantTimePlayer pretty consistently but still lose to BetterPlayer pretty hard. Even though this is the case, I think the assignment was still a good experience because it introduced a lot of interesting concepts that we understood on some level even though we didn't end up implementing them.
