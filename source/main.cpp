#include <borealis.hpp>
#include <switch.h>

#include "utils/constants.hpp"
#include "utils/games.hpp"
#include "utils/config.hpp"
#include "views/recycling_list_tab.hpp"
#include "views/settings_tab.hpp"
#include "views/favorite_tab.hpp"

#include "activity/main_activity.hpp"

int main(int argc, char* argv[]) {
    brls::Logger::setLogLevel(brls::LogLevel::LOG_DEBUG);
    //brls::Application::enableDebuggingView(true);
    
    {
        cfg::Config config;
        if (config.getAppLanguage() != "auto") {
            brls::Platform::APP_LOCALE_DEFAULT = config.getAppLanguage();
            brls::Logger::debug("Loaded translations for language {}", config.getAppLanguage());
        }
    }

    if(!brls::Application::init()) {
        brls::Logger::error("Unable to init Borealis application");
        return -1;
    }

    brls::loadTranslations();

    brls::Application::createWindow(fmt::format("UpcomingSwitchGames {}.{}.{}", MAJOR_VERSION, MINOR_VERSION, REVISION_VERSION));
    brls::Application::getPlatform()->setThemeVariant(brls::ThemeVariant::DARK);
    brls::Application::setGlobalQuit(false);

    brls::Application::registerXMLView("RecyclingListTab", RecyclingListTab::create);
    brls::Application::registerXMLView("FavoritesTab", FavoriteGamesTab::create);
    brls::Application::registerXMLView("SettingsTab", SettingsTab::create);

    // Add custom values to the theme
    brls::Theme::getLightTheme().addColor("captioned_image/caption", nvgRGB(2, 176, 183));
    brls::Theme::getDarkTheme().addColor("captioned_image/caption", nvgRGB(51, 186, 227));

    // Add custom values to the style
    brls::getStyle().addMetric("about/padding_top_bottom", 50);
    brls::getStyle().addMetric("about/padding_sides", 75);
    brls::getStyle().addMetric("about/description_margin", 50);

    brls::Application::pushActivity(new MainActivity());

    while(brls::Application::mainLoop()) ;

    return -1;
}