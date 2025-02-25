class Twitter {
private:
    vector<vector<int>> fol;
    vector<pair<int, int>> tweets;

public:
    Twitter() : fol(501, vector<int>(501, 0)), tweets(0) {}

    void postTweet(int userId, int tweetId) {
        tweets.push_back(pair<int, int>(userId, tweetId));
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        for (int i = tweets.size() - 1; i >= 0 && res.size() < 10; --i) {
            if (userId == tweets[i].first || fol[userId][tweets[i].first]) {
                res.push_back(tweets[i].second);
            }
        }
        return res;
    }

    void follow(int followerId, int followeeId) {
        fol[followerId][followeeId] = 1;
    }

    void unfollow(int followerId, int followeeId) {
        fol[followerId][followeeId] = 0;
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
