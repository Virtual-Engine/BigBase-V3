#include "common.hpp"
#include "base_tab.h"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "../../util.hpp"

namespace big
{
	void base_tab::render_base_tab()
	{
		bool o_bool{};
		const double min = 0., max = 10.;
		int slider = 0;
		const char* const demo_combo[]
		{
			"One",
			"Two",
			"Three"
		};

		if (ImGui::Begin("BigBase"))
		{
			ImGui::Checkbox("Bool", &o_bool);
			ImGui::SliderInt("Int", &slider, 0, 10);

			ImGui::SameLine();

			if (ImGui::Button("Unload"))
			{
				g_running = false;
			}
		}
		ImGui::End();
	}
}
