#pragma once
#include <string>
#include <vector>

namespace DiscordPlusPlus {
	struct User;
	struct Connection;
	struct Guild;
	struct GuildEmbed;
	struct GuildMember;
	struct Integration;
	struct IntegrationAccount;
	struct Ban;
	struct Channel;
	struct Message;
	struct Embed;
	struct EmbedThumbnail;
	struct EmbedFooter;
	struct EmbedImage;
	struct EmbedVideo;
	struct EmbedProvider;
	struct EmbedAuthor;
	struct EmbedFeild;
	struct Attachment;
	struct Invite;
	struct InviteMetadata;
	struct VoideState;
	struct VoiceRegion;
	struct Webhook;

	struct User
	{
	public:
		std::string id;
		std::string username;
		std::string discriminator;
		std::string avatar;
		bool verified;
		bool bot;
		bool mfa_enabled;
		std::string email;
	};

	struct Connection
	{
	public:
		std::string id;
		std::string name;
		std::string type;
		//std::vector<??> integrations;
	};

	struct Guild
	{
	public:
		std::string id;
		std::string name;
		std::string icon; 
		std::string splash;
		std::string owner_id;
		std::string region;
		std::string afk_channel_id;
		int afk_timeout;
		bool embed_enabled;
		std::string embed_channel_id;
		int verification_level;
		int default_message_notifications;
		int explicit_content_filter;
		//std::vector<Role> roles;
		//std::vector<Emoji> emojis;
		std::vector<std::string> features;
		int mfa_level;
		std::string application_id;
		bool widget_enabled;
		std::string widget_channel_id;
		//Timestamp
		bool large;
		bool unavailable;
		int member_count;
		//std::vector<VoiceState> voice_states;
		std::vector<GuildMember> members;
		std::vector<Channel> channels;
		//std::vector<PresenceUpdate> presences;
	};

	struct GuildEmbed
	{
	public:
		bool enabled;
		std::string channel_id;
	};

	struct GuildMember
	{
	public:
		User user;
		std::string nickname;
		//Roles TODO
		//Timestamp
		bool deaf;
		bool mute;
	};

	struct Integration
	{
	public:
		std::string id;
		std::string name;
		std::string type;
		bool enabled;
		bool syncing;
		int expire_behavior;
		int expire_grace_period;
		User user;
		//Account account;
		//Timestamp
	};

	struct IntegrationAccount
	{
	public:
		std::string id;
		std::string name;
	};

	struct Ban
	{
	public:
		std::string reason;
		User user;
	};

	struct Channel
	{
	public:
		std::string id;
		int type;
		std::string guild_id;
		int position;
		//Overwrite array
		std::string name;
		std::string topic;
		bool nsfw;
		std::string last_message_id;
		int bitrate;
		int user_limit;
		std::vector<User> recepients;
		std::string icon;
		std::string owner_id;
		std::string application_id;
		std::string parent_id;
	};

	struct Message
	{
	public:
		std::string id;
		std::string channel_id;
		User author;
		std::string content;
		//timestamp
		//timestamp that can be null
		bool tts;
		bool mention_everyone;
		std::vector<User> mentions;
		//std::vector<Role> mention_roles;
		//std::vector<Attachment> attachments;
		//std::vector<Embed> embeds;
		//std::vector<Reaction> reactions;
		std::string nonce;
		bool pinned;
		std::string webhook_id;
		int type;
	};

	struct Embed
	{
		std::string title;
		std::string type;
		std::string description;
		std::string url;
		//Timestamp
		int color;
		EmbedFooter footer;
		EmbedImage image;
		EmbedThumbnail thumbnail;
		EmbedVideo video;
		EmbedProvider provider;
		EmbedAuthor author;
		std::vector<EmbedField> fields;
	};

	struct EmbedVideo
	{
	public:
		std::string url;
		int height;
		int width;
	};

	struct EmbedThumbnail
	{
	public:
		std::string url;
		std::string proxy_url;
		int height;
		int width;
	};

	struct EmbedImage
	{
	public:
		std::string url;
		std::string proxy_url;
		int height;
		int width;
	};

	struct EmbedProvider
	{
	public:
		std::string name;
		std::string url;
	};

	struct EmbedAuthor
	{
	public:
		std::string name;
		std::string url;
		std::string icon_url;
		std::string proxy_icon_url;
	};

	struct EmbedFooter
	{
	public:
		std::string text;
		std::string icon_url;
		std::string proxy_icon_url;
	};

	struct EmbedField
	{
	public:
		std::string name;
		std::string value;
		bool is_inline;
	};

	struct Attachment
	{
	public:
		std::string id;
		std::string filename;
		int size;
		std::string url;
		std::string proxy_url;
		int height;
		int width;
	};

	struct Invite
	{
	public:
		std::string code;
		Guild guild;
		Channel channel;
	};

	struct InviteMetadata
	{
	public:
		User inviter;
		int uses;
		int max_uses;
		int max_age;
		bool temporary;
		//Timestamp
		bool revoked;
	};

	struct VoiceState
	{
	public:
		std::string guild_id;
		std::string channel_id;
		std::string user_id;
		std::string session_id;
		bool deaf;
		bool mute;
		bool self_deaf;
		bool self_mute;
		bool suppress;
	};

	struct VoiceRegion
	{
	public:
		std::string id;
		std::string name;
		std::string sample_hosename;
		std::string sample_port;
		bool vip;
		bool optimal;
		bool deprecated;
		bool custom;
	};

	struct Webhook 
	{
	public:
		std::string id;
		std::string guild_id;
		std::string channel_id;
		User user;
		std::string name;
		std::string avatar;
		std::string token;
	};

}