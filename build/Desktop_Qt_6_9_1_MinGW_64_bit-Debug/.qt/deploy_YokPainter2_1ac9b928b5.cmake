include("D:/studying/cpp/YokPainter2/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/YokPainter2-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE D:/studying/cpp/YokPainter2/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/YokPainter2.exe
    GENERATE_QT_CONF
)
